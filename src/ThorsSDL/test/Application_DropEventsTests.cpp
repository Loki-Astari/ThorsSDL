#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(DropFile, SDL_DropEvent, SDL_DROPFILE)
HANDLER_TEST(DropText, SDL_DropEvent, SDL_DROPTEXT)
HANDLER_TEST(DropBegin, SDL_DropEvent, SDL_DROPBEGIN)
HANDLER_TEST(DropEnd, SDL_DropEvent, SDL_DROPCOMPLETE)

