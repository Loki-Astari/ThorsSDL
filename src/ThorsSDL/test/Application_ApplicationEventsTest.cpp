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

HANDLER_TEST(Application_ApplicationEventsTest, Quit, SDL_QuitEvent, SDL_QUIT)
HANDLER_TEST(Application_ApplicationEventsTest, BackgroundEnterAboutTo, SDL_CommonEvent, SDL_APP_WILLENTERBACKGROUND)
HANDLER_TEST(Application_ApplicationEventsTest, BackgroundEnterDone, SDL_CommonEvent, SDL_APP_DIDENTERBACKGROUND)
HANDLER_TEST(Application_ApplicationEventsTest, ForegroundEnterAboutTo, SDL_CommonEvent, SDL_APP_WILLENTERFOREGROUND)
HANDLER_TEST(Application_ApplicationEventsTest, ForegroundEnterDone, SDL_CommonEvent, SDL_APP_DIDENTERFOREGROUND)
HANDLER_TEST(Application_ApplicationEventsTest, Terminating, SDL_CommonEvent, SDL_APP_TERMINATING)
HANDLER_TEST(Application_ApplicationEventsTest, LowMemory, SDL_CommonEvent, SDL_APP_LOWMEMORY)
HANDLER_TEST(Application_ApplicationEventsTest, LocalUpdate, SDL_CommonEvent, SDL_LOCALECHANGED)

