#ifndef THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H
#define THORSANVIL_WIDGETS_WIDGET_EXAMPLE_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"

namespace ThorsAnvil::Widgets
{

class WidgetExample: public Widget
{
    public:
        WidgetExample(WidgetView& parent);
        virtual ~WidgetExample();

        virtual void draw(UI::DrawContext& drawContext)     override;
        virtual void updateState()                          override;
        virtual void reset()                                override;

    public:
        // Layout Functions;
        virtual UI::Pt  preferredLayout(Layout const& layout) const override;
        virtual void    performLayout(Layout const& layout) override;
};

}

#endif
