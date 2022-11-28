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

HANDLER_TEST(Application_GestureEventsTests, DollarGesture, SDL_DollarGestureEvent, SDL_DOLLARGESTURE)
HANDLER_TEST(Application_GestureEventsTests, DollarRecord, SDL_DollarGestureEvent, SDL_DOLLARRECORD)
HANDLER_TEST(Application_GestureEventsTests, MultiGesture, SDL_MultiGestureEvent, SDL_MULTIGESTURE)

