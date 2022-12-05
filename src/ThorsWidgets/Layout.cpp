#include "Layout.h"
#include "Widget.h"

using namespace ThorsAnvil::Widgets;


Layout::~Layout()
{}

UI::Pt BoxLayout::preferredLayout(Widget& widget) const
{
    return widget.preferredLayout(*this);
}

void BoxLayout::performLayout(Widget& widget) const
{
    widget.performLayout(*this);
}
