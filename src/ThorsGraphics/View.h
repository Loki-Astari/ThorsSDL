#ifndef THORSANVIL_GRAPHICS_VIEW_H
#define THORSANVIL_GRAPHICS_VIEW_H

#include "ThorsGraphicsConfig.h"
#include "ThorsUI/View.h"
#include <gtest/gtest_prod.h>
#include <vector>

namespace ThorsAnvil::UI
{
    class Window;
    class DrawContext;
}

class ViewTest_CheckSpriteStored_Test;
namespace ThorsAnvil::Graphics
{

namespace UI = ThorsAnvil::UI;

class Sprite;
class View: public UI::View
{
    FRIEND_TEST(::ViewTest, CheckSpriteStored);
    std::vector<Sprite*>        sprites;

    public:
        View(UI::Window& window);
        virtual void updateState() override;
        virtual UI::Sz reset(bool fitWindowToView) override;
        virtual void draw(UI::DrawContext& context) override;

        void addSprite(Sprite& sprite);
        void remSprite(Sprite& sprite);
};

}

#endif
