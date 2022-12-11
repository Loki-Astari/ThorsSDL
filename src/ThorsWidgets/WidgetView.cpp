#include "WidgetView.h"
#include "Widget.h"
#include "Layout.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Widgets;

WidgetView::WidgetView(WidgetView& parent, Layout& layout)
    : Widget(parent, {0, 0})
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
    theme.drawWidgetView(drawContext);
    layout.drawWidget(drawContext, theme, widgets);
}

ThorsAnvil::UI::Sz WidgetView::doPreferredLayout(Theme const& theme, ThorsAnvil::UI::Sz /*size*/)
{
    return layout.preferredLayout(theme, widgets);
}

void WidgetView::doPerformLayout(ThorsAnvil::UI::Pt topLeft, Theme const& theme)
{
    layout.performLayout(topLeft, theme, widgets);
}
