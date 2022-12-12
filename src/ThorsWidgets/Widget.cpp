#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(WidgetView& parent, UI::Sz size, bool visible)
    : parent(parent)
    , size(size)
    , lastUpdate{}
    , visible{visible}
{
    parent.addWidget(*this);
}

Widget::~Widget()
{
    parent.remWidget(*this);
}

UI::Sz Widget::preferredLayout(UI::DrawContext& drawContext, Theme const& theme)
{
    size = doPreferredLayout(drawContext, theme, size);
    return size;
}

void Widget::performLayout(UI::Pt newTopLeft, Theme const& theme)
{
    topLeft = newTopLeft;
    doPerformLayout(newTopLeft, theme);
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

void Widget::handleEventMouseMoveInWidgetAction(SDL_MouseMotionEvent const& /*event*/)
{}

void Widget::handleEventMouseMoveEnterWidget()
{}

void Widget::handleEventMouseMoveLeaveWidget()
{}
