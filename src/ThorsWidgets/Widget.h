#ifndef THORSANVIL_UI_WIDGET_H
#define THORSANVIL_UI_WIDGET_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Widgets
{

class WidgetView;
class Widget
{
    WidgetView&        parent;
    UI::TimePoint       lastUpdate;
    int                 updatePeriod;

    public:
        Widget(WidgetView& parent, int millisecondUpdateTime);
        virtual ~Widget();

        void updateState();

        virtual void doDraw(UI::DrawContext& drawContext)   = 0;
        virtual bool doUpdateState()                        = 0;
        virtual void reset();
};

}

#endif
