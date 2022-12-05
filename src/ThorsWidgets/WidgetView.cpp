#include "WidgetView.h"
#include "Widget.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Widgets;

void WidgetView::updateState()
{
    for (auto const& widget: widgets)
    {
        widget->updateState();
    }
}

void WidgetView::WidgetView::reset()
{
    for (auto const& widget: widgets)
    {
        widget->reset();
    }
}

void WidgetView::draw(ThorsAnvil::UI::DrawContext& context)
{
    for (auto const& widget: widgets)
    {
        widget->draw(context);
    }
}

void WidgetView::addWidget(Widget& widget)
{
    widgets.emplace_back(&widget);
}

void WidgetView::remWidget(Widget& widget)
{
    auto find = std::find(std::begin(widgets), std::end(widgets), &widget);
    if (find != std::end(widgets))
    {
        widgets.erase(find);
    }
}
