#include "WidgetView.h"
#include "Widget.h"
#include "Layout.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Widgets;

WidgetView::WidgetView(WidgetView& parent, Layout& layout)
    : Widget(parent, {0, 0})
    , layout(layout)
    , mouseOver(nullptr)
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
    theme.drawWidget(drawContext, *this);
    layout.drawWidget(drawContext, theme, widgets);
}

UI::Sz WidgetView::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz /*size*/)
{
    return layout.preferredLayout(drawContext, theme, widgets);
}

void WidgetView::doPerformLayout(UI::Pt topLeft, Theme const& theme)
{
    layout.performLayout(topLeft, theme, widgets);
}

void WidgetView::handleEventMouseMoveInWidgetAction(SDL_MouseMotionEvent const& event)
{
    for (auto& widget: widgets)
    {
        if (widget->handleEventMouseMoveInWidget(event))
        {
            if (widget != mouseOver)
            {
                if (mouseOver != nullptr) {
                    mouseOver->handleEventMouseMoveLeaveWidget();
                }
                mouseOver = widget;
                mouseOver->handleEventMouseMoveEnterWidget();
            }
            return;
        }
    }
    if (mouseOver)
    {
        mouseOver->handleEventMouseMoveLeaveWidget();
        mouseOver = nullptr;
    }
}

void WidgetView::handleEventMouseMoveEnterWidget()
{}

void WidgetView::handleEventMouseMoveLeaveWidget()
{
    if (mouseOver) {
        mouseOver->handleEventMouseMoveLeaveWidget();
    }
    mouseOver = nullptr;
}
