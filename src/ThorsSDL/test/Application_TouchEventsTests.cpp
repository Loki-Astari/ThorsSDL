#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(FingerDown, SDL_TouchFingerEvent, SDL_FINGERDOWN)
HANDLER_TEST(FingerUp, SDL_TouchFingerEvent, SDL_FINGERUP)
HANDLER_TEST(FingerMotion, SDL_TouchFingerEvent, SDL_FINGERMOTION)

