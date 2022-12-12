#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include "ThorsUI/DrawContext.h"
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
        ThorsAnvil::UI::Application         application;
        ThorsAnvil::UI::Window              window("Test", {10, 10, 100, 100});
        ThorsAnvil::Graphics::View          view(window);
        TestSprite                          sprite(view, 0);
    };

    EXPECT_NO_THROW(
        action()
    );

}

