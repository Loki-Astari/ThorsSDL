#include "test/WindowTest.h"

    /* Mouse events             0x040*  */
WIN_HANDLER_TEST(MouseMove, SDL_MouseMotionEvent, SDL_MOUSEMOTION)
WIN_HANDLER_TEST(MouseDown, SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN)
WIN_HANDLER_TEST(MouseUp, SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP)
WIN_HANDLER_TEST(MouseWheel, SDL_MouseWheelEvent, SDL_MOUSEWHEEL)

