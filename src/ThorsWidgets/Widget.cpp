#include "Widget.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(WidgetView& parent, int millisecondUpdateTime)
    : parent(parent)
    , lastUpdate{}
    , updatePeriod(millisecondUpdateTime)
{
    parent.addWidget(*this);
}

Widget::~Widget()
{
    parent.remWidget(*this);
}

void Widget::updateState()
{
    UI::TimePoint   now =  std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= updatePeriod)
    {
        if (doUpdateState())
        {
            lastUpdate = now;
        }
    }
}

void Widget::doDraw(UI::DrawContext& /*drawContext*/)
{}

bool Widget::doUpdateState()
{
    return true;
}

void Widget::reset()
{}
