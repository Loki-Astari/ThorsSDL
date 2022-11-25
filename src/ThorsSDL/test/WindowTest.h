#ifndef THORSANVIL_UI_TEST_WINDOW_TEST_H
#define THORSANVIL_UI_TEST_WINDOW_TEST_H

#include "gtest/gtest.h"
#include "coverage/ThorMock.h"
#include "Window.h"
#include "Application.h"
#include <stdexcept>

#define WIN_HANDLER_TEST(Handler, EventType, EventId)               WIN_HANDLER_TEST_FULL(Handler, EventType, EventId, false, 0)
#define WIN_HANDLER_WIN_TEST(Handler, EventType, winEventId)        WIN_HANDLER_TEST_FULL(Handler, EventType, SDL_WINDOWEVENT, true, winEventId)
#define WIN_HANDLER_TEST_FULL(Handler, EventType, EventId, isWin, winEventId)   \
struct Window ## Handler: public ThorsAnvil::UI::DebugWindow                    \
{                                                                               \
    int& count;                                                                 \
    Uint32& eventType;                                                          \
    Uint32& winEventType;                                                       \
    Window ## Handler(ThorsAnvil::UI::Application& application, int& count, Uint32& eventType, Uint32& winEventType)   \
        : DebugWindow(application, "Test Window", {100, 100, 200, 200})         \
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
TEST(WindowTest, CheckEventHandler ## Handler)                                  \
{                                                                               \
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});                           \
    MOCK_SYS(SDL_Quit,        [](){});                                          \
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event* event){                             \
        static int returnValue = 1;                                             \
        event->type = EventId;                                                  \
        reinterpret_cast<EventType*>(event)->windowID = 1;                      \
        if constexpr (isWin)                                                    \
        {                                                                       \
            event->window.event = winEventId;                                   \
        }                                                                       \
        return returnValue--;                                                   \
    });                                                                         \
                                                                                \
    auto createWindowMock       = [](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {return reinterpret_cast<SDL_Window*>(1);};    \
    auto destroyWindowMock      = [](SDL_Window*){};                                                                                                    \
    auto createRendererMock     = [](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {return reinterpret_cast<SDL_Renderer*>(2);};                        \
    auto destroyRendererMock    = [](SDL_Renderer*){};                                                                                                  \
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;};                                                                    \
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;};                                                            \
    auto renderClearMock        = [](SDL_Renderer*){ return 0;};                \
    auto renderPresentMock      = [](SDL_Renderer*){};                          \
    auto getWindowIdMock        = [](SDL_Window* win) -> Uint32 {return 1;};    \
                                                                                \
    MOCK_SYS(SDL_CreateWindow,      createWindowMock);                          \
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);                         \
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);                        \
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);                       \
    MOCK_SYS(SDL_SetHint,           setHintMock);                               \
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);                    \
    MOCK_SYS(SDL_RenderClear,       renderClearMock);                           \
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);                         \
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);                           \
                                                                                \
    int count = 0;                                                              \
    Uint32 eventType = 0;                                                       \
    Uint32 winEventType = 0;                                                    \
                                                                                \
    auto action = [&count, &eventType, &winEventType]()                         \
    {                                                                           \
        ThorsAnvil::UI::Application     application;                            \
        Window ## Handler               window(application, count, eventType, winEventType);    \
                                                                                \
        application.eventLoop([](){}, [&application](int){application.exitLoop();});            \
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
