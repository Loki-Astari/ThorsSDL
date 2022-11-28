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

HANDLER_TEST(Application_RenderEventsTests, RenderTargetReset, SDL_CommonEvent, SDL_RENDER_TARGETS_RESET)
HANDLER_TEST(Application_RenderEventsTests, RenderDeviceReset, SDL_CommonEvent, SDL_RENDER_DEVICE_RESET)

