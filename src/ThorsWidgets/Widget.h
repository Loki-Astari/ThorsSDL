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
struct Theme;
class Widget
{
    WidgetView&         parent;
    UI::TimePoint       lastUpdate;
    bool                visible;

    public:
        Widget(WidgetView& parent, bool visible = true);
        virtual ~Widget();

        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)= 0;
        virtual UI::Sz  preferredLayout(Theme const& theme)                         = 0;
        virtual void    performLayout(UI::Pt topLeft, Theme const& theme)           = 0;


        bool    isVisible() const   {return visible;}

};

}

#endif
