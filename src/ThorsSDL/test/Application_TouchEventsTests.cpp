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

HANDLER_TEST(FingerDown, SDL_TouchFingerEvent, SDL_FINGERDOWN)
HANDLER_TEST(FingerUp, SDL_TouchFingerEvent, SDL_FINGERUP)
HANDLER_TEST(FingerMotion, SDL_TouchFingerEvent, SDL_FINGERMOTION)

