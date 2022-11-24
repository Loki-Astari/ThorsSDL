#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(Quit, SDL_QuitEvent, SDL_QUIT)
HANDLER_TEST(Terminating, SDL_CommonEvent, SDL_APP_TERMINATING)
HANDLER_TEST(LowMemory, SDL_CommonEvent, SDL_APP_LOWMEMORY)
HANDLER_TEST(LocalUpdate, SDL_CommonEvent, SDL_LOCALECHANGED)

