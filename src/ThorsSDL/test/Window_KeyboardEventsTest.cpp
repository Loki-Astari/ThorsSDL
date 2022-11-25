#include "test/WindowTest.h"

    /* Keyboard events          0x030*  */
WIN_HANDLER_TEST(KeyDown, SDL_KeyboardEvent, SDL_KEYDOWN)
WIN_HANDLER_TEST(KeyUp, SDL_KeyboardEvent, SDL_KEYUP)
WIN_HANDLER_TEST(TextEditting, SDL_TextEditingEvent, SDL_TEXTEDITING)
WIN_HANDLER_TEST(TextInput, SDL_TextInputEvent, SDL_TEXTINPUT)
WIN_HANDLER_TEST(TextEditingExt, SDL_TextEditingExtEvent, SDL_TEXTEDITING_EXT)


