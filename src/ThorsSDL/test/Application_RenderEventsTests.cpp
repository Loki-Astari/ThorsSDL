#include "gtest/gtest.h"
#include "test/ApplicationTest.h"

HANDLER_TEST(RenderTargetReset, SDL_CommonEvent, SDL_RENDER_TARGETS_RESET)
HANDLER_TEST(RenderDeviceReset, SDL_CommonEvent, SDL_RENDER_DEVICE_RESET)

