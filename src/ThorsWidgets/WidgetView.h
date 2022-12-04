#ifndef THORSANVIL_WIDGETS_WIDGET_VIEW_H
#define THORSANVIL_WIDGETS_WIDGET_VIEW_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/View.h"
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
class WidgetView: public UI::View
{
    FRIEND_TEST(::WidgetViewTest, CheckWidgetStored);
    std::vector<Widget*>        sprites;

    public:
        virtual void updateState() override;
        virtual void reset() override;
        virtual void doDraw(UI::DrawContext& context) override;

        void addWidget(Widget& sprite);
        void remWidget(Widget& sprite);
};

}

#endif
