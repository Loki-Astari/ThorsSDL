#ifndef THORSANVIL_WIDGETS_WIDGET_H
#define THORSANVIL_WIDGETS_WIDGET_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Widgets
{

class Layout;
class WidgetView;
class Widget
{
    WidgetView&        parent;
    UI::TimePoint       lastUpdate;

    public:
        Widget(WidgetView& parent);
        virtual ~Widget();

        virtual void draw(UI::DrawContext& drawContext)     = 0;
        virtual void updateState()                          = 0;
        virtual void reset();

    public:
        // Layout Functions;
        virtual UI::Pt  preferredLayout(Layout const& layout) const = 0;
        virtual void    performLayout(Layout const& layout)         = 0;

};

}

#endif
