#include "gtest/gtest.h"
#include "coverage/ThorMock.h"
#include "Application.h"
#include "Window.h"
#include <stdexcept>

TEST(ApplicationTest, CreateAnApplication)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
    };

    EXPECT_NO_THROW(
        action()
    );
    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
}

TEST(ApplicationTest, CreateTwoApplication)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    auto action = []()
    {
        ThorsAnvil::UI::Application     application1;
        ThorsAnvil::UI::Application     application2;
    };
    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
}

TEST(ApplicationTest, SDL_InitFails)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return -1;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(0, quitCallCount);
}

TEST(ApplicationTest, InitSubSystemOK)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int subSysCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_InitSubSystem, [&subSysCallCount](Uint32){++subSysCallCount;return 0;});

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.initSubSystem(ThorsAnvil::UI::Video);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, subSysCallCount);
}

TEST(ApplicationTest, InitSubSystemFail)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int subSysCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_InitSubSystem, [&subSysCallCount](Uint32){++subSysCallCount;return -1;});

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.initSubSystem(ThorsAnvil::UI::Video);
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );
    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, subSysCallCount);
}

TEST(ApplicationTest, QuitSubSystemCalled)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int subSysCallCount = 0;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_QuitSubSystem, [&subSysCallCount](Uint32){++subSysCallCount;});

    auto action = []()
    {
        ThorsAnvil::UI::Application     application(ThorsAnvil::UI::Timer);

        application.quitSubSystem(ThorsAnvil::UI::Timer);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, subSysCallCount);
}

TEST(ApplicationTest, PollNoEventsAndExit)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int pollCount = 0;
    int eventCountGot = -1;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_PollEvent,   [&pollCount](SDL_Event*){++pollCount;return 0;});

    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;

        application.eventLoop([](){}, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, pollCount);
    EXPECT_EQ(0, eventCountGot);
}

TEST(ApplicationTest, EventLoopShouldNotThrowExceptionsButExitNormally)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int pollCount = 0;
    int eventCountGot = -1;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_PollEvent,   [&pollCount](SDL_Event*){++pollCount;return 0;});

    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;

        application.eventLoop([](){}, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; throw std::runtime_error("Should be caught");});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, pollCount);
    EXPECT_EQ(0, eventCountGot);
}

TEST(ApplicationTest, CheckWindowIsRegisteredByCheckingCallsToGetWindowId)
{
    int initCallCount = 0;
    int quitCallCount = 0;
    int pollCount = 0;
    int eventCountGot = -1;
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_PollEvent,   [&pollCount](SDL_Event*){++pollCount;return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return reinterpret_cast<SDL_Window*>(1);};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return reinterpret_cast<SDL_Renderer*>(2);};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window*){++windowId;return 1;};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = [&eventCountGot]()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});

        application.eventLoop([](){}, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, createWindow);
    EXPECT_EQ(1, destroyWindow);
    EXPECT_EQ(1, createRender);
    EXPECT_EQ(1, destroyRender);
    EXPECT_EQ(2, windowId);

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(1, pollCount);
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
    int initCallCount = 0;
    int quitCallCount = 0;
    int pollCount = 0;
    int eventCountGot = -1;
    int methodCall = 0;
    Uint32 eventType = 0;

    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});
    MOCK_SYS(SDL_PollEvent,   [&pollCount](SDL_Event* event){
        static int returnValue = 1;
        EXPECT_NE(nullptr, event);
        ++pollCount;
        event->type = SDL_QUIT;
        return returnValue--;
    });

    auto action = [&eventCountGot, &methodCall, &eventType]()
    {
        ApplicationQuitOrig     application(methodCall, eventType);

        application.eventLoop([](){}, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, initCallCount);
    EXPECT_EQ(1, quitCallCount);
    EXPECT_EQ(2, pollCount);
    EXPECT_EQ(1, eventCountGot);
    EXPECT_EQ(1, methodCall);
    EXPECT_EQ(SDL_QUIT, eventType);
}

