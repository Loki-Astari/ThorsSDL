#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "Application.h"
#include "Window.h"
#include "DrawContext.h"
#include "Sprite.h"

class TestSprite: public ThorsAnvil::UI::Sprite
{
    public:
        using Sprite::Sprite;

        virtual void doDraw(ThorsAnvil::UI::DrawContext&)   override    {}
        virtual bool doUpdateState()        override    {return true;}
};

TEST(SpriteTest, WindowConstruction)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = [](){
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {10, 10, 20, 20});

        TestSprite                      sprite(window, 0, 0);
        EXPECT_EQ(1, window.sprites.size());

        application.eventLoop(1000, [&application](int){application.exitLoop();});
    };

    EXPECT_NO_THROW(
        action()
    );

}

