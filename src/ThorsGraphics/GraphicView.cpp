#include "GraphicView.h"
#include "Sprite.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Graphics;

void GraphicView::updateState()
{
    for (auto const& sprite: sprites) {
        sprite->updateState();
    }
}

ThorsAnvil::UI::Sz GraphicView::GraphicView::reset()
{
    for (auto const& sprite: sprites) {
        sprite->reset();
    }
    return {0, 0};
}

void GraphicView::draw(ThorsAnvil::UI::DrawContext& context)
{
    for (auto const& sprite: sprites) {
        sprite->draw(context);
    }
}

void GraphicView::addSprite(Sprite& sprite)
{
    sprites.emplace_back(&sprite);
}

void GraphicView::remSprite(Sprite& sprite)
{
    auto find = std::find(std::begin(sprites), std::end(sprites), &sprite);
    if (find != std::end(sprites)) {
        sprites.erase(find);
    }
}
