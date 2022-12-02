#include "test/WindowTest.h"
#include "Sprite.h"

TEST(WindowTest, WindowConstruction)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(2, actions.count[countSDL_GetWindowID]);
}

TEST(WindowTest, WindowConstruction_WindowCreateFails)
{
    MocksSDLActions     actions{.mockSDL_CreateWindow = [](char const*, int, int, int, int, Uint32) {return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(0, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(0, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(0, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(0, actions.count[countSDL_GetWindowID]);
}

TEST(WindowTest, WindowConstruction_RenderCreateFails)
{
    MocksSDLActions     actions{.mockSDL_CreateRenderer = [](SDL_Window*, int, Uint32) {return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(0, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(2, actions.count[countSDL_GetWindowID]);
}

TEST(WindowTest, WindowMoveConstruction)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst(std::move(src));
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(3, actions.count[countSDL_GetWindowID]);
}

TEST(WindowTest, WindowMoveAssignment)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst("Next", {20, 20, 10, 10});

        dst = std::move(src);
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(2, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(2, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(2, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(2, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(5, actions.count[countSDL_GetWindowID]);
}

class MockSprite: public ThorsAnvil::UI::Sprite
{
    int&    resetCount;
    public:
        MockSprite(ThorsAnvil::UI::Window& parent, int& resetCount)
            : Sprite(parent, 0, 10)
            , resetCount(resetCount)
        {}

        virtual void doDraw(ThorsAnvil::UI::DrawContext& drawContext)   {}
        virtual bool doUpdateState()                    {return true;}
        virtual void reset()                            {++resetCount;Sprite::reset();}
};

TEST(WindowTest, WindowUpdateLayout)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);
    int                 resetCount = 0;

    auto action = [&resetCount]()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});

        MockSprite                      sprite(window, resetCount);

        window.updateLayer(0);
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateWindow]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyWindow]);
    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
    EXPECT_EQ(2, actions.count[countSDL_GetWindowID]);
    EXPECT_EQ(1, resetCount);
}

