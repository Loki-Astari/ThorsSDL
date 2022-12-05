#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(WidgetView& parent)
    : parent(parent)
    , lastUpdate{}
{
    parent.addWidget(*this);
}

Widget::~Widget()
{
    parent.remWidget(*this);
}

void Widget::updateState()
{}

void Widget::draw(UI::DrawContext& /*drawContext*/)
{}

void Widget::reset()
{}
