#ifndef THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H
#define THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class WidgetExample: public Widget
{
    public:
        WidgetExample(WidgetView& parent);
        virtual ~WidgetExample();

        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;
};

}

#endif
