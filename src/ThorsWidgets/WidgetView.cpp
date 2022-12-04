#include "WidgetView.h"
#include "Widget.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Widgets;

void WidgetView::updateState()
{
    for (auto const& sprite: sprites)
    {
        sprite->updateState();
    }
}

void WidgetView::WidgetView::reset()
{
    for (auto const& sprite: sprites)
    {
        sprite->reset();
    }
}

void WidgetView::doDraw(ThorsAnvil::UI::DrawContext& context)
{
    for (auto const& sprite: sprites)
    {
        sprite->doDraw(context);
    }
}

void WidgetView::addWidget(Widget& sprite)
{
    sprites.emplace_back(&sprite);
}

void WidgetView::remWidget(Widget& sprite)
{
    auto find = std::find(std::begin(sprites), std::end(sprites), &sprite);
    if (find != std::end(sprites))
    {
        sprites.erase(find);
    }
}
