#ifndef THORSANVIL_UI_TEST_APPLICATION_TEST_H
#define THORSANVIL_UI_TEST_APPLICATION_TEST_H

#include "coverage/ThorMock.h"
#include "DebugApplication.h"
#include <stdexcept>

#define HANDLER_TEST(Handler, EventType, EventId)                  HANDLER_TEST_FULL(Handler, EventType, EventId, false, 0)
#define HANDLER_WIN_TEST(Handler, EventType, EventId)              HANDLER_TEST_FULL(Handler, EventType, SDL_WINDOWEVENT, true, EventId)

#define HANDLER_TEST_FULL(Handler, EventType, EventId, isWin, winEventId)   \
struct Application ## Handler: public ThorsAnvil::UI::DebugApplication      \
{                                                                           \
    int& count;                                                             \
    Uint32& eventType;                                                      \
    Application ## Handler (int& count, Uint32& eventType)                  \
        : DebugApplication()                                                \
        , count(count)                                                      \
        , eventType(eventType)                                              \
    {}                                                                      \
    virtual void handleEvent ## Handler (EventType const& event) override   \
    {                                                                       \
        ++count;                                                            \
        eventType = event.type;                                             \
        try { DebugApplication::handleEvent ## Handler(event); }catch(...){}     \
    }                                                                       \
};                                                                          \
                                                                            \
TEST(ApplicationTest, CheckEventHandler ## Handler )                        \
{                                                                           \
    int initCallCount = 0;                                                  \
    int quitCallCount = 0;                                                  \
    int pollCount = 0;                                                      \
    int eventCountGot = -1;                                                 \
    int methodCall = 0;                                                     \
    Uint32 eventEventId = 0;                                                \
                                                                            \
    MOCK_SYS(SDL_Init,        [&initCallCount](Uint32){++initCallCount;return 0;});  \
    MOCK_SYS(SDL_Quit,        [&quitCallCount](){++quitCallCount;});        \
    MOCK_SYS(SDL_PollEvent,   [&pollCount](SDL_Event* event){               \
        static int returnValue = 1;                                         \
        EXPECT_NE(nullptr, event);                                          \
        ++pollCount;                                                        \
        event->type = EventId;                                              \
        if constexpr (isWin)                                                \
        {                                                                   \
            event->window.event = winEventId;                               \
        }                                                                   \
        return returnValue--;                                               \
    });                                                                     \
                                                                            \
    auto action = [&eventCountGot, &methodCall, &eventEventId]()            \
    {                                                                       \
        Application ## Handler     application(methodCall, eventEventId);   \
                                                                            \
        application.eventLoop([](){}, [&application, &eventCountGot](int eventCount){eventCountGot = eventCount; application.exitLoop();});  \
    };                                                                      \
                                                                            \
    EXPECT_NO_THROW(                                                        \
        action();                                                           \
    );                                                                      \
                                                                            \
    EXPECT_EQ(1, initCallCount);                                            \
    EXPECT_EQ(1, quitCallCount);                                            \
    EXPECT_EQ(2, pollCount);                                                \
    EXPECT_EQ(1, eventCountGot);                                            \
    EXPECT_EQ(1, methodCall);                                               \
    EXPECT_EQ(EventId, eventEventId);                                       \
}

#endif

