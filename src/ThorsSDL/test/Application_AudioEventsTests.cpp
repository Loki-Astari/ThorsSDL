#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(AudioDeviceAdd, SDL_AudioDeviceEvent, SDL_AUDIODEVICEADDED)
HANDLER_TEST(AudioDeviceRem, SDL_AudioDeviceEvent, SDL_AUDIODEVICEREMOVED)

