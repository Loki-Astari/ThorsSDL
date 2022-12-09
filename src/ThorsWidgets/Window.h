#ifndef THORSANVIL_WIDGETS_WINDOW_H
#define THORSANVIL_WIDGETS_WINDOW_H

#include "ThorsWidgetsConfig.h"
#include "WidgetView.h"
#include "ThorsSDL/View.h"

namespace ThorsAnvil::Widgets
{

struct Theme;
class Layout;
class Window: public WidgetView, public UI::View
{
    Theme&          theme;
    UI::Sz          size;

    public:
        Window(Layout& layout, Theme& theme);
        void tile();

        virtual void draw(UI::DrawContext& context) override;
        virtual UI::Sz reset() override;
#if 0
        Widget:
            virtual void    drawWidget(UI::DrawContext& drawContext, Theme& theme)= 0;
            virtual UI::Sz  preferredLayout() const                         = 0;
            virtual void    performLayout(UI::Pt topLeft)                   = 0;
#endif

};

}

#endif
