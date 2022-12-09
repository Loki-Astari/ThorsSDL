#include "WidgetView.h"
#include "Widget.h"
#include "Layout.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Widgets;

WidgetView::WidgetView(WidgetView& parent, Layout& layout)
    : Widget(parent)
    , layout(layout)
{}

void WidgetView::addWidget(Widget& widget)
{
    widgets.emplace_back(&widget);
}

void WidgetView::remWidget(Widget& widget)
{
    auto find = std::find(std::begin(widgets), std::end(widgets), &widget);
    if (find != std::end(widgets)) {
        widgets.erase(find);
    }
}

void WidgetView::drawWidget(UI::DrawContext& drawContext, Theme const& theme)
{
    for (auto widget: widgets)
    {
        if (widget->isVisible()) {
            widget->drawWidget(drawContext, theme);
        }
    }
}

ThorsAnvil::UI::Sz WidgetView::preferredLayout(Theme const& theme)
{
    layout.clear();
    for (auto widget: widgets)
    {
        if (widget->isVisible()) {
            layout.addWidget(widget->preferredLayout(theme));
        }
    }
    return layout.getSize(theme);
}

void WidgetView::performLayout(ThorsAnvil::UI::Pt topLeft, Theme const& theme)
{
    int index = 0;
    for (auto widget: widgets)
    {
        if (widget->isVisible())
        {
            ThorsAnvil::UI::Sz offset = layout.getOffset(index++);
            widget->performLayout(topLeft + offset, theme);
        }
    }
}
