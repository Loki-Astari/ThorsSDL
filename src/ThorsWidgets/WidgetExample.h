#ifndef THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H
#define THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::Widgets
{

class WidgetExample: public Widget
{
    public:
        WidgetExample(WidgetView& parent);
        virtual ~WidgetExample();

        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;
};

}

#endif
