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

HANDLER_TEST(Application_MouseEventsTests, MouseMove, SDL_MouseMotionEvent, SDL_MOUSEMOTION)
HANDLER_TEST(Application_MouseEventsTests, MouseDown, SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN)
HANDLER_TEST(Application_MouseEventsTests, MouseUp, SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP)
HANDLER_TEST(Application_MouseEventsTests, MouseWheel, SDL_MouseWheelEvent, SDL_MOUSEWHEEL)

