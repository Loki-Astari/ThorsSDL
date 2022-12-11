#include "Layout.h"
#include "Widget.h"
#include <algorithm>

using namespace ThorsAnvil::Widgets;

Layout::Layout(bool removeNonVisibleWidgets)
    : removeNonVisibleWidgets(removeNonVisibleWidgets)
{}

Layout::~Layout()
{}

ThorsAnvil::UI::Sz Layout::preferredLayout(Theme const& theme, std::vector<Widget*>& widgets)
{
    layoutSize.clear();

    int index = 0;
    int max = maxWidgets();
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        if (index >= max) {
            continue;
        }
        layoutSize.emplace_back(widget->preferredLayout(theme));
        ++index;
    }
    return getSize(theme);
}

void Layout::performLayout(ThorsAnvil::UI::Pt topLeft, Theme const& theme, std::vector<Widget*>& widgets)
{
    int index = 0;
    int max = maxWidgets();
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        if (index >= max) {
            continue;
        }
        ThorsAnvil::UI::Sz offset = offsetPoint[index];
        widget->performLayout(topLeft + offset, theme);
        ++index;
    }
}

void Layout::drawWidget(UI::DrawContext& drawContext, Theme const& theme, std::vector<Widget*>& widgets)
{
    int index = 0;
    int max = maxWidgets();
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        if (index >= max) {
            continue;
        }
        widget->drawWidget(drawContext, theme);
        ++index;
    }
}
