#include "gtest/gtest.h"
#include "coverage/ThorMock.h"
#include "Application.h"
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

struct ApplicationQuitOrig: public ThorsAnvil::UI::Application
{
    int& count;
    Uint32& eventType;
    ApplicationQuitOrig(int& count, Uint32& eventType)
        : Application()
        , count(count)
        , eventType(eventType)
    {}
    virtual void handleEventQuit(SDL_QuitEvent const& event){++count;eventType = event.type;}
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

