#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(WidgetView& parent, ThorsAnvil::UI::Sz size, bool visible)
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

ThorsAnvil::UI::Sz Widget::preferredLayout(Theme const& theme)
{
    size = doPreferredLayout(theme, size);
    return size;
}

void Widget::performLayout(UI::Pt newTopLeft, Theme const& theme)
{
    topLeft = newTopLeft;
    doPerformLayout(newTopLeft, theme);
}
