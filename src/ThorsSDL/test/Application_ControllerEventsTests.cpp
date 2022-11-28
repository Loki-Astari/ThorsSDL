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

HANDLER_TEST(Application_ControllerEventsTests, ControlMotion, SDL_ControllerAxisEvent, SDL_CONTROLLERAXISMOTION)
HANDLER_TEST(Application_ControllerEventsTests, ControlButtonDown, SDL_ControllerButtonEvent, SDL_CONTROLLERBUTTONDOWN)
HANDLER_TEST(Application_ControllerEventsTests, ControlButtonUp, SDL_ControllerButtonEvent, SDL_CONTROLLERBUTTONUP)
HANDLER_TEST(Application_ControllerEventsTests, ControlDeviceAdd, SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEADDED)
HANDLER_TEST(Application_ControllerEventsTests, ControlDeviceRem, SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEREMOVED)
HANDLER_TEST(Application_ControllerEventsTests, ControlDeviceMap, SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEREMAPPED)

HANDLER_TEST(Application_ControllerEventsTests, TouchPadDown, SDL_ControllerTouchpadEvent, SDL_CONTROLLERTOUCHPADDOWN)
HANDLER_TEST(Application_ControllerEventsTests, TouchPadUp, SDL_ControllerTouchpadEvent, SDL_CONTROLLERTOUCHPADUP)
HANDLER_TEST(Application_ControllerEventsTests, TouchPadMotion, SDL_ControllerTouchpadEvent, SDL_CONTROLLERTOUCHPADMOTION)
HANDLER_TEST(Application_ControllerEventsTests, TouchPadSendor, SDL_ControllerSensorEvent, SDL_CONTROLLERSENSORUPDATE)

