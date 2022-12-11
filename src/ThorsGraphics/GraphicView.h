#ifndef THORSANVIL_GRAPHICS_GRAPHIC_VIEW_H
#define THORSANVIL_GRAPHICS_GRAPHIC_VIEW_H

#include "ThorsGraphicsConfig.h"
#include "ThorsSDL/View.h"
#include <gtest/gtest_prod.h>
#include <vector>

namespace ThorsAnvil::UI
{
    class Window;
    class DrawContext;
}

class GraphicViewTest_CheckSpriteStored_Test;
namespace ThorsAnvil::Graphics
{

namespace UI = ThorsAnvil::UI;

class Sprite;
class GraphicView: public UI::View
{
    FRIEND_TEST(::GraphicViewTest, CheckSpriteStored);
    std::vector<Sprite*>        sprites;

    public:
        GraphicView(UI::Window& window);
        virtual void updateState() override;
        virtual UI::Sz reset() override;
        virtual void draw(UI::DrawContext& context) override;

        void addSprite(Sprite& sprite);
        void remSprite(Sprite& sprite);
};

}

#endif
