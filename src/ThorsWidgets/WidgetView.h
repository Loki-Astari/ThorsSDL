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

namespace UI = ThorsAnvil::UI;

class Widget;
class Layout;
class TextInputSet;
class MouseFocusSet;
class WidgetView: public Widget
{
    FRIEND_TEST(::WidgetViewTest, CheckWidgetStored);
    Layout&                     layout;
    std::vector<Widget*>        widgets;
    Widget*                     mouseOver;

    public:
        WidgetView(Layout& layout);
        WidgetView(WidgetView& parent, Layout& layout);

    private:
        friend class Widget;
        void addWidget(Widget& sprite);
        void remWidget(Widget& sprite);

    private:
        // Drawing the View.
        // Delegates to theme and Layout.
        //      Theme does any drawing specific to the View.
        //      then layout simply calls each child widget to draw itself.
        friend class View;
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

    private:
        // The Layout class handles all the layout stuff to do with Widgets.
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        virtual void    doPerformLayout(UI::Pt topLeft, Theme const& theme) override;
};

}

#endif
