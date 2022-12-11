#ifndef THORSANVIL_WIDGETS_WINDOW_H
#define THORSANVIL_WIDGETS_WINDOW_H

#include "ThorsWidgetsConfig.h"
#include "WidgetView.h"
#include "ThorsSDL/View.h"

namespace ThorsAnvil::UI
{
    class Window;
}

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class Layout;
class Window: public WidgetView, public UI::View
{
    Theme&          theme;
    UI::Sz          size;

    public:
        Window(UI::Window& window, Layout& layout, Theme& theme);
        void tile();

        virtual void draw(UI::DrawContext& context) override;
        virtual UI::Sz reset() override;
#if 0
        Widget:
            virtual void    drawWidget(UI::DrawContext& drawContext, Theme& theme)= 0;
            virtual UI::Sz  doPreferredLayout(.....) const                  = 0;
            virtual void    doPerformLayout(UI::Pt topLeft)                 = 0;
#endif

};

}

#endif
