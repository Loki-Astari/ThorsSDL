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

HANDLER_TEST(DropFile, SDL_DropEvent, SDL_DROPFILE)
HANDLER_TEST(DropText, SDL_DropEvent, SDL_DROPTEXT)
HANDLER_TEST(DropBegin, SDL_DropEvent, SDL_DROPBEGIN)
HANDLER_TEST(DropEnd, SDL_DropEvent, SDL_DROPCOMPLETE)

