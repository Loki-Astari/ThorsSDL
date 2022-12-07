#ifndef THORSANVIL_WIDGETS_WIDGET_VIEW_H
#define THORSANVIL_WIDGETS_WIDGET_VIEW_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include <gtest/gtest_prod.h>
#include <vector>

namespace ThorsAnvil::UI
{
    class DrawContext;
}

class WidgetViewTest_CheckWidgetStored_Test;
namespace ThorsAnvil::Widgets
{

class Widget;
class Layout;
class WidgetView: public Widget
{
    FRIEND_TEST(::WidgetViewTest, CheckWidgetStored);
    Layout&                     layout;
    std::vector<Widget*>        widgets;

    public:
        WidgetView(WidgetView& parent, Layout& layout);

        void addWidget(Widget& sprite);
        void remWidget(Widget& sprite);

        // Widget
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)    override;
        virtual UI::Sz  preferredLayout(Theme const& theme)                             override;
        virtual void    performLayout(UI::Pt topLeft, Theme const& theme)               override;
};

}

#endif
