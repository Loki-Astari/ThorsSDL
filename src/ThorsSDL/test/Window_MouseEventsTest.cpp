#include "test/WindowTest.h"

    /* Mouse events             0x040*  */
WIN_HANDLER_TEST(Window_MouseEventsTest, MouseMove, SDL_MouseMotionEvent, SDL_MOUSEMOTION)
WIN_HANDLER_TEST(Window_MouseEventsTest, MouseDown, SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN)
WIN_HANDLER_TEST(Window_MouseEventsTest, MouseUp, SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP)
WIN_HANDLER_TEST(Window_MouseEventsTest, MouseWheel, SDL_MouseWheelEvent, SDL_MOUSEWHEEL)

