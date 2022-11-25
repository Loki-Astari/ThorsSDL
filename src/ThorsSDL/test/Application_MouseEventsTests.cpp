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

HANDLER_TEST(MouseMove, SDL_MouseMotionEvent, SDL_MOUSEMOTION)
HANDLER_TEST(MouseDown, SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN)
HANDLER_TEST(MouseUp, SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP)
HANDLER_TEST(MouseWheel, SDL_MouseWheelEvent, SDL_MOUSEWHEEL)

