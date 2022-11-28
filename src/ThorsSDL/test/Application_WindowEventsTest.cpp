#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

/*
 * HANDLER_TEST defined in test/ApplicationTest.h
 *
 * Look in test/ApplicationTest.cpp to see a fully expanded version of this macro.
 *
 * The Type: ApplicationQuitOrig
 * And Test: CheckEventHandlerQuitOrig
 *
 * are a fully expanded version of the macro to help in finding bugs.
 */

HANDLER_WIN_TEST(Application_WindowEventsTest, WindowShow, SDL_WindowEvent, SDL_WINDOWEVENT_SHOWN)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowHide, SDL_WindowEvent, SDL_WINDOWEVENT_HIDDEN)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowExpose, SDL_WindowEvent, SDL_WINDOWEVENT_EXPOSED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowMoved, SDL_WindowEvent, SDL_WINDOWEVENT_MOVED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowResized, SDL_WindowEvent, SDL_WINDOWEVENT_RESIZED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowSizeChange, SDL_WindowEvent, SDL_WINDOWEVENT_SIZE_CHANGED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowMin, SDL_WindowEvent, SDL_WINDOWEVENT_MINIMIZED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowMax, SDL_WindowEvent, SDL_WINDOWEVENT_MAXIMIZED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowRestore, SDL_WindowEvent, SDL_WINDOWEVENT_RESTORED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowEnter, SDL_WindowEvent, SDL_WINDOWEVENT_ENTER)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowLeave, SDL_WindowEvent, SDL_WINDOWEVENT_LEAVE)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowFocusGain, SDL_WindowEvent, SDL_WINDOWEVENT_FOCUS_GAINED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowFocusLost, SDL_WindowEvent, SDL_WINDOWEVENT_FOCUS_LOST)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowClose, SDL_WindowEvent, SDL_WINDOWEVENT_CLOSE)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowTakeFocus, SDL_WindowEvent, SDL_WINDOWEVENT_TAKE_FOCUS)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowHitTest, SDL_WindowEvent, SDL_WINDOWEVENT_HIT_TEST)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowICCProfChange, SDL_WindowEvent, SDL_WINDOWEVENT_ICCPROF_CHANGED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowDisplayChange, SDL_WindowEvent, SDL_WINDOWEVENT_DISPLAY_CHANGED)
HANDLER_WIN_TEST(Application_WindowEventsTest, WindowUnknown, SDL_WindowEvent, -1)

