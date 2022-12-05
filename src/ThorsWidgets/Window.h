#ifndef THORSANVIL_WIDGETS_WINDOW_H
#define THORSANVIL_WIDGETS_WINDOW_H

#include "ThorsWidgetsConfig.h"
#include "WidgetView.h"

namespace ThorsAnvil::Widgets
{

class Theme;
class Layout;
class Window: public WidgetView
{
    Theme&          theme;
    Layout&         layout;

    public:
        Window(Theme& theme, Layout& layout);
        //virtual void updateState() override;
        //virtual void reset() override;
        //virtual void doDraw(UI::DrawContext& context) override;

        //void addWidget(Widget& sprite);
        //void remWidget(Widget& sprite);
};

}

#endif
