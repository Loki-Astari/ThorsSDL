#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(WidgetView& parent, bool visible)
    : parent(parent)
    , lastUpdate{}
    , visible{visible}
{
    parent.addWidget(*this);
}

Widget::~Widget()
{
    parent.remWidget(*this);
}
