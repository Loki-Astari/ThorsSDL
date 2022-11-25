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

HANDLER_TEST(JoyMotion, SDL_JoyAxisEvent, SDL_JOYAXISMOTION)
HANDLER_TEST(JoyBall, SDL_JoyBallEvent, SDL_JOYBALLMOTION)
HANDLER_TEST(JoyHat, SDL_JoyHatEvent, SDL_JOYHATMOTION)
HANDLER_TEST(JoyButtonDown, SDL_JoyButtonEvent, SDL_JOYBUTTONDOWN)
HANDLER_TEST(JoyButtonUp, SDL_JoyButtonEvent, SDL_JOYBUTTONUP)
HANDLER_TEST(JoyDeviceAdd, SDL_JoyDeviceEvent, SDL_JOYDEVICEADDED)
HANDLER_TEST(JoyDeviceRem, SDL_JoyDeviceEvent, SDL_JOYDEVICEREMOVED)
HANDLER_TEST(JoyBattery, SDL_JoyBatteryEvent, SDL_JOYBATTERYUPDATED)

