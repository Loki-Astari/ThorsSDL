#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/DrawContext.h"
#include "Sprite.h"

class TestSprite: public ThorsAnvil::Graphics::Sprite
{
    public:
        using Sprite::Sprite;

        virtual void draw(ThorsAnvil::UI::DrawContext&)   override    {}
        virtual bool doUpdateState()        override    {return true;}
};

TEST(SpriteTest, Construct)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::Graphics::GraphicView   view;
        TestSprite                      sprite(view, 0);
    };

    EXPECT_NO_THROW(
        action()
    );

}

