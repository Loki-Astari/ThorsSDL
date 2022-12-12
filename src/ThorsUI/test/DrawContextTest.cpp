#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "DrawContext.h"

TEST(DrawContextTest, CreateEmptyContext)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::DrawContext     context;
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_TRUE(actions.noSDLCalled());
}

TEST(DrawContextTest, CreateContextFromWindow)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::DrawContext     context(reinterpret_cast<SDL_Window*>(1));
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
}

TEST(DrawContextTest, CreateContextFromWindowRenderFail)
{
    MocksSDLActions     actions{.mockSDL_CreateRenderer = [](SDL_Window*, int, Uint32) -> SDL_Renderer* {return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::DrawContext     context(reinterpret_cast<SDL_Window*>(1));
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(0, actions.count[countSDL_DestroyRenderer]);
}

TEST(DrawContextTest, CreateContextFromWindowAndMoveConstruct)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::DrawContext     src(reinterpret_cast<SDL_Window*>(1));
        ThorsAnvil::UI::DrawContext     dst(std::move(src));

        dst = std::move(src);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
}

TEST(DrawContextTest, CreateContextFromWindowAndMoveAssignment)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::DrawContext     dst;
        ThorsAnvil::UI::DrawContext     src(reinterpret_cast<SDL_Window*>(1));

        dst = std::move(src);
    };

    EXPECT_NO_THROW(
        action()
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
}

TEST(DrawContextTest, GetSurface)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    EXPECT_NO_THROW(
        ThorsAnvil::UI::DrawContext     src(reinterpret_cast<SDL_Window*>(1));

        EXPECT_NE(nullptr, src.getRenderer());

        ThorsAnvil::UI::DrawContext     dst(std::move(src));
        EXPECT_EQ(nullptr, src.getRenderer());
        EXPECT_NE(nullptr, dst.getRenderer());

        ThorsAnvil::UI::DrawContext     dst2;
        EXPECT_EQ(nullptr, dst2.getRenderer());

        dst2 = std::move(src);
        EXPECT_EQ(nullptr, dst2.getRenderer());

        dst2 = std::move(dst);
        EXPECT_NE(nullptr, dst2.getRenderer());
        EXPECT_EQ(nullptr, dst.getRenderer());
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateRenderer]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyRenderer]);
}

