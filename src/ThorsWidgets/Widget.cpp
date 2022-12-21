#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(UI::Sz minSize, bool visible)
    : parentWidget(nullptr)
    , size{0, 0}
    , minSize(minSize)
    , lastUpdate{}
    , visible{visible}
{}

Widget::Widget(WidgetView& parentWidgetParam, UI::Sz minSize, bool visible)
    : parentWidget(&parentWidgetParam)
    , size{0, 0}
    , minSize(minSize)
    , lastUpdate{}
    , visible{visible}
{
    parentWidget->addWidget(*this);
}

Widget::~Widget()
{
    if (parentWidget) {
        parentWidget->remWidget(*this);
    }
}

UI::Sz Widget::preferredLayout(UI::DrawContext& drawContext, Theme const& theme)
{
    size = doPreferredLayout(drawContext, theme, size);
    size.x = std::max(size.x, minSize.x);
    size.y = std::max(size.y, minSize.y);

    return size;
}

void Widget::performLayout(UI::Pt newTopLeft, Theme const& theme)
{
    topLeft = newTopLeft;
    doPerformLayout(newTopLeft, theme);
}

void Widget::markDirty()
{
    if (parentWidget == nullptr) {
        throw std::runtime_error("Root Widget should override");
    }

    parentWidget->markDirty();
}

bool Widget::handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event)
{
    UI::Rect rect = getBoundingRect();

    if (!rect.contains({event.x, event.y}))
    {
        return false;
    }
    handleEventMouseMoveInWidgetAction(event);
    return true;
}

Widget* Widget::handleEventMouseUpInWidget(Widget* mouseDownIn)
{
    return mouseDownIn;
}
