#include "gtest/gtest.h"
#include "test/ApplicationTest.h"
#include "Application.h"
#include "Window.h"
#include <stdexcept>

TEST(ApplicationTest, CreateAnApplication)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
    };

    EXPECT_NO_THROW(
        action()
    );
    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
}

TEST(ApplicationTest, CreateTwoApplication)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application1;
        ThorsAnvil::UI::Application     application2;
    };
    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Init);
}

TEST(ApplicationTest, SDL_InitFails)
{
    MocksSDLActions     actions{.mockSDL_Init = [](Uint32){return -1;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(0, actions.countSDL_Quit);
}

TEST(ApplicationTest, InitSubSystemOK)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.initSubSystem(ThorsAnvil::UI::Video);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_InitSubSystem);
}

TEST(ApplicationTest, InitSubSystemFail)
{
    MocksSDLActions     actions{.mockSDL_InitSubSystem = [](Uint32){return -1;}};;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.initSubSystem(ThorsAnvil::UI::Video);
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_InitSubSystem);
}

TEST(ApplicationTest, QuitSubSystemCalled)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.quitSubSystem(ThorsAnvil::UI::Timer);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_QuitSubSystem);
}

TEST(ApplicationTest, PollNoEventsAndExit)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    int eventCountGot = -1;
    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;

        application.eventLoop(60, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_PollEvent);
    EXPECT_EQ(0, eventCountGot);
}

TEST(ApplicationTest, EventLoopShouldNotThrowExceptionsButExitNormally)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    int eventCountGot = -1;
    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;

        application.eventLoop(60, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; throw std::runtime_error("Should be caught");});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_PollEvent);
    EXPECT_EQ(0, eventCountGot);
}

TEST(ApplicationTest, CheckWindowIsRegisteredByCheckingCallsToGetWindowId)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    int eventCountGot = -1;
    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});

        application.eventLoop(60, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(1, actions.countSDL_PollEvent);
    EXPECT_EQ(1, actions.countSDL_CreateWindow);
    EXPECT_EQ(1, actions.countSDL_DestroyWindow);
    EXPECT_EQ(1, actions.countSDL_CreateRenderer);
    EXPECT_EQ(1, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(2, actions.countSDL_GetWindowID);

    EXPECT_EQ(0, eventCountGot);
}

struct ApplicationQuitOrig: public ThorsAnvil::UI::Application
{
    int& count;
    Uint32& eventType;
    ApplicationQuitOrig(int& count, Uint32& eventType)
        : Application()
        , count(count)
        , eventType(eventType)
    {}
    virtual void handleEventQuit(SDL_QuitEvent const& event)    override {++count;eventType = event.type;}
};

TEST(ApplicationTest, CheckEventHandlerQuitOrig)
{
    MocksSDLActions     actions{.mockSDL_PollEvent = [](SDL_Event* event){
        static int returnValue = 1;
        event->type = SDL_QUIT;
        return returnValue--;
    }};
    MockSDL             mockActivate(actions);

    int eventCountGot = -1;
    int methodCall = 0;
    Uint32 eventType = 0;
    auto action = [&eventCountGot, &methodCall, &eventType]()
    {
        ApplicationQuitOrig     application(methodCall, eventType);

        application.eventLoop(60, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_Init);
    EXPECT_EQ(1, actions.countSDL_Quit);
    EXPECT_EQ(2, actions.countSDL_PollEvent);

    EXPECT_EQ(1, eventCountGot);
    EXPECT_EQ(1, methodCall);
    EXPECT_EQ(SDL_QUIT, eventType);
}

