#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(MouseMove, SDL_MouseMotionEvent, SDL_MOUSEMOTION)
HANDLER_TEST(MouseDown, SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN)
HANDLER_TEST(MouseUp, SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP)
HANDLER_TEST(MouseWheel, SDL_MouseWheelEvent, SDL_MOUSEWHEEL)

