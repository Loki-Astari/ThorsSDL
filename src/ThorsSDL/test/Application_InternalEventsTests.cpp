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

HANDLER_TEST(SystemEvent, SDL_SysWMEvent, SDL_SYSWMEVENT)
HANDLER_TEST(PollSentinel, SDL_CommonEvent, SDL_POLLSENTINEL)
HANDLER_TEST(Unknown, SDL_CommonEvent, -1)

