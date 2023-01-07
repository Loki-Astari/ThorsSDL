#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "Surface.h"

TEST(SurfaceTest, TextureCreate)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Surface         surface;
    };

    EXPECT_NO_THROW(
        action();
    );
}

