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

    public:
        // Widget
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)    override;
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size)              override;
        virtual void    doPerformLayout(UI::Pt topLeft, Theme const& theme)             override;

        virtual void    handleEventMouseMoveInWidgetAction(SDL_MouseMotionEvent const& event) override;
        virtual void    handleEventMouseMoveEnterWidget() override;
        virtual void    handleEventMouseMoveLeaveWidget() override;
        virtual Widget* handleEventMouseDownInWidget() override;
        virtual Widget* handleEventMouseUpInWidget(Widget* mouseDownIn) override;
        virtual void    handleEventMouseUpOutsideWidget() override;
        virtual Widget* acceptTextFocus() override;
};

}

#endif
