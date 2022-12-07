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
class Theme;
class Widget
{
    WidgetView&        parent;
    UI::TimePoint       lastUpdate;

    public:
        Widget(WidgetView& parent);
        virtual ~Widget();

        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)= 0;
        virtual UI::Sz  preferredLayout(Theme const& theme)                         = 0;
        virtual void    performLayout(UI::Pt topLeft, Theme const& theme)           = 0;

};

}

#endif
