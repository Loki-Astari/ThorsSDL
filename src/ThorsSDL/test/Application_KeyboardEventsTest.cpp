#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(KeyDown, SDL_KeyboardEvent, SDL_KEYDOWN)
HANDLER_TEST(KeyUp, SDL_KeyboardEvent, SDL_KEYUP)
HANDLER_TEST(TextEditting, SDL_TextEditingEvent, SDL_TEXTEDITING)
HANDLER_TEST(TextInput, SDL_TextInputEvent, SDL_TEXTINPUT)
HANDLER_TEST(TextEditingExt, SDL_TextEditingExtEvent, SDL_TEXTEDITING_EXT)
HANDLER_TEST(KeyMapChanged, SDL_CommonEvent, SDL_KEYMAPCHANGED)
