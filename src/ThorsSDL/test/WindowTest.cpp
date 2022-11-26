#include "test/WindowTest.h"

TEST(WindowTest, WindowConstruction)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_CreateWindow);
    EXPECT_EQ(1, actions.countSDL_DestroyWindow);
    EXPECT_EQ(1, actions.countSDL_CreateRenderer);
    EXPECT_EQ(1, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(2, actions.countSDL_GetWindowID);
}

TEST(WindowTest, WindowConstruction_WindowCreateFails)
{
    MocksSDLActions     actions{.mockSDL_CreateWindow = [](char const*, int, int, int, int, Uint32) {return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.countSDL_CreateWindow);
    EXPECT_EQ(0, actions.countSDL_DestroyWindow);
    EXPECT_EQ(0, actions.countSDL_CreateRenderer);
    EXPECT_EQ(0, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(0, actions.countSDL_GetWindowID);
}

TEST(WindowTest, WindowConstruction_RenderCreateFails)
{
    MocksSDLActions     actions{.mockSDL_CreateRenderer = [](SDL_Window*, int, Uint32) {return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.countSDL_CreateWindow);
    EXPECT_EQ(1, actions.countSDL_DestroyWindow);
    EXPECT_EQ(1, actions.countSDL_CreateRenderer);
    EXPECT_EQ(0, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(0, actions.countSDL_GetWindowID);
}

TEST(WindowTest, WindowMoveConstruction)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src(application, "Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst(std::move(src));
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.countSDL_CreateWindow);
    EXPECT_EQ(1, actions.countSDL_DestroyWindow);
    EXPECT_EQ(1, actions.countSDL_CreateRenderer);
    EXPECT_EQ(1, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(3, actions.countSDL_GetWindowID);
}

TEST(WindowTest, WindowMoveAssignment)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src(application, "Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst(application, "Next", {20, 20, 10, 10});

        dst = std::move(src);
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(2, actions.countSDL_CreateWindow);
    EXPECT_EQ(2, actions.countSDL_DestroyWindow);
    EXPECT_EQ(2, actions.countSDL_CreateRenderer);
    EXPECT_EQ(2, actions.countSDL_DestroyRenderer);
    EXPECT_EQ(5, actions.countSDL_GetWindowID);
}

