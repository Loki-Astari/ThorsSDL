#include "View.h"
#include "Sprite.h"
#include "ThorsUI/DrawContext.h"

using namespace ThorsAnvil::Graphics;

View::View(UI::Window& window)
    : UI::View(window)
{}

void View::updateState()
{
    for (auto const& sprite: sprites) {
        sprite->updateState();
    }
}

UI::Sz View::View::reset(bool)
{
    for (auto const& sprite: sprites) {
        sprite->reset();
    }
    return {0, 0};
}

void View::draw(UI::DrawContext& context)
{
    for (auto const& sprite: sprites) {
        sprite->draw(context);
    }
}

void View::addSprite(Sprite& sprite)
{
    sprites.emplace_back(&sprite);
}

void View::remSprite(Sprite& sprite)
{
    auto find = std::find(std::begin(sprites), std::end(sprites), &sprite);
    if (find != std::end(sprites)) {
        sprites.erase(find);
    }
}
