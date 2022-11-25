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

HANDLER_TEST(Quit, SDL_QuitEvent, SDL_QUIT)
HANDLER_TEST(Terminating, SDL_CommonEvent, SDL_APP_TERMINATING)
HANDLER_TEST(LowMemory, SDL_CommonEvent, SDL_APP_LOWMEMORY)
HANDLER_TEST(LocalUpdate, SDL_CommonEvent, SDL_LOCALECHANGED)

