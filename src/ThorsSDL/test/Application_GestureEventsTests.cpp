#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(DollarGesture, SDL_DollarGestureEvent, SDL_DOLLARGESTURE)
HANDLER_TEST(DollarRecord, SDL_DollarGestureEvent, SDL_DOLLARRECORD)
HANDLER_TEST(MultiGesture, SDL_MultiGestureEvent, SDL_MULTIGESTURE)

