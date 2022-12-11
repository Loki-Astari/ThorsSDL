#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/DrawContext.h"
#include "Sprite.h"

struct MockSprite: public ThorsAnvil::Graphics::Sprite
{
    using Sprite::Sprite;

    int drawCount   = 0;
    int updateCount = 0;
    int resetCount  = 0;

        virtual void draw(ThorsAnvil::UI::DrawContext& drawContext)     {++drawCount;Sprite::draw(drawContext);}
        virtual bool doUpdateState()                                    {++updateCount;return Sprite::doUpdateState();}
        virtual void reset()                                            {++resetCount;Sprite::reset();}
};

TEST(GraphicViewTest, CheckSpriteStored)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::Application         application;
        ThorsAnvil::UI::Window              window("Test", {10, 10, 100, 100});
        ThorsAnvil::Graphics::GraphicView   view(window);

        {
            MockSprite  sprite(view, 0);
            EXPECT_EQ(1, view.sprites.size());
        }
        EXPECT_EQ(0, view.sprites.size());
    };

    EXPECT_NO_THROW(
        action()
    );
}

TEST(GraphicViewTest, RunDraw)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::Application         application;
        ThorsAnvil::UI::Window              window("Test", {10, 10, 100, 100});
        ThorsAnvil::Graphics::GraphicView   view(window);
        MockSprite                          sprite(view, 0);

        view.draw(*reinterpret_cast<ThorsAnvil::UI::DrawContext*>(1));

        EXPECT_EQ(1, sprite.drawCount);
        EXPECT_EQ(0, sprite.updateCount);
        EXPECT_EQ(0, sprite.resetCount);
    };

    EXPECT_NO_THROW(
        action()
    );
}

TEST(GraphicViewTest, RunUpdate)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::Application         application;
        ThorsAnvil::UI::Window              window("Test", {10, 10, 100, 100});
        ThorsAnvil::Graphics::GraphicView   view(window);
        MockSprite                          sprite(view, 0);

        view.updateState();

        EXPECT_EQ(0, sprite.drawCount);
        EXPECT_EQ(1, sprite.updateCount);
        EXPECT_EQ(0, sprite.resetCount);
    };

    EXPECT_NO_THROW(
        action()
    );
}

TEST(GraphicViewTest, RunReset)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::Application         application;
        ThorsAnvil::UI::Window              window("Test", {10, 10, 100, 100});
        ThorsAnvil::Graphics::GraphicView   view(window);
        MockSprite                          sprite(view, 0);

        view.reset();

        EXPECT_EQ(0, sprite.drawCount);
        EXPECT_EQ(0, sprite.updateCount);
        EXPECT_EQ(1, sprite.resetCount);
    };

    EXPECT_NO_THROW(
        action()
    );
}

