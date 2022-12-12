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

HANDLER_TEST(Application_KeyboardEventsTest, KeyDown, SDL_KeyboardEvent, SDL_KEYDOWN)
HANDLER_TEST(Application_KeyboardEventsTest, KeyUp, SDL_KeyboardEvent, SDL_KEYUP)
HANDLER_TEST(Application_KeyboardEventsTest, TextEditting, SDL_TextEditingEvent, SDL_TEXTEDITING)
HANDLER_TEST(Application_KeyboardEventsTest, TextInput, SDL_TextInputEvent, SDL_TEXTINPUT)
HANDLER_TEST(Application_KeyboardEventsTest, TextEditingExt, SDL_TextEditingExtEvent, SDL_TEXTEDITING_EXT)
HANDLER_TEST(Application_KeyboardEventsTest, KeyMapChanged, SDL_CommonEvent, SDL_KEYMAPCHANGED)

