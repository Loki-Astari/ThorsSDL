#ifndef THORSANVIL_UI_TEST_WINDOW_TEST_H
#define THORSANVIL_UI_TEST_WINDOW_TEST_H

#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "Window.h"
#include "Application.h"
#include <stdexcept>

#define WIN_HANDLER_TEST(Test, Handler, EventType, EventId)               WIN_HANDLER_TEST_FULL(Test, Handler, EventType, EventId, false, 0)
#define WIN_HANDLER_WIN_TEST(Test, Handler, EventType, winEventId)        WIN_HANDLER_TEST_FULL(Test, Handler, EventType, SDL_WINDOWEVENT, true, winEventId)
#define WIN_HANDLER_TEST_FULL(Test, Handler, EventType, EventId, isWin, winEventId)   \
struct Window ## Handler: public ThorsAnvil::UI::DebugWindow                    \
{                                                                               \
    int& count;                                                                 \
    Uint32& eventType;                                                          \
    Uint32& winEventType;                                                       \
    Window ## Handler(int& count, Uint32& eventType, Uint32& winEventType)   \
        : DebugWindow("Test Window", {100, 100, 200, 200})         \
        , count(count)                                                          \
        , eventType(eventType)                                                  \
        , winEventType(winEventType)                                            \
    {}                                                                          \
    virtual void handleEvent ## Handler(EventType const& event) override        \
    {                                                                           \
        ++count;                                                                \
        eventType = event.type;                                                 \
        if constexpr (isWin)                                                    \
        {                                                                       \
           winEventType = reinterpret_cast<SDL_WindowEvent const&>(event).event;\
        }                                                                       \
        DebugWindow::handleEvent ## Handler(event);                             \
    }                                                                           \
};                                                                              \
                                                                                \
TEST(Test, CheckEventHandler ## Handler)                                        \
{                                                                               \
    int windowId = -1;                                                          \
    MocksSDLActions     actions{.mockSDL_PollEvent = [&windowId](SDL_Event* event){      \
        static int returnValue = 1;                                             \
        event->type = EventId;                                                  \
        reinterpret_cast<EventType*>(event)->windowID = windowId;               \
        if constexpr (isWin)                                                    \
        {                                                                       \
            event->window.event = winEventId;                                   \
        }                                                                       \
        return returnValue--;                                                   \
    }};                                                                         \
    MockSDL             mockActivate(actions);                                  \
                                                                                \
    int count = 0;                                                              \
    Uint32 eventType = 0;                                                       \
    Uint32 winEventType = 0;                                                    \
    auto action = [&count, &eventType, &winEventType, &windowId]()              \
    {                                                                           \
        ThorsAnvil::UI::Application     application;                            \
        Window ## Handler               window(count, eventType, winEventType);    \
        windowId = window.getId();                                              \
                                                                                \
        application.eventLoop(60, [&application](int){application.exitLoop();});            \
    };                                                                          \
                                                                                \
    EXPECT_NO_THROW(                                                            \
        action();                                                               \
    );                                                                          \
                                                                                \
    EXPECT_EQ(1, count);                                                        \
    EXPECT_EQ(EventId, eventType);                                              \
    if constexpr (isWin)                                                        \
    {                                                                           \
        EXPECT_EQ(winEventId, winEventType);                                    \
    }                                                                           \
}

#endif
