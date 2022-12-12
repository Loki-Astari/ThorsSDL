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

HANDLER_TEST(Application_AudioEventsTests, AudioDeviceAdd, SDL_AudioDeviceEvent, SDL_AUDIODEVICEADDED)
HANDLER_TEST(Application_AudioEventsTests, AudioDeviceRem, SDL_AudioDeviceEvent, SDL_AUDIODEVICEREMOVED)

