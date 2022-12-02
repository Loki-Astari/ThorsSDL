#ifndef THORSANVIL_UI_WIDGET_WIDGET_H
#define THORSANVIL_UI_WIDGET_WIDGET_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/DrawContext.h"
#include "ThorsSDL/Util.h"
#include <vector>

namespace ThorsAnvil::Widget
{

class Widget;
class Layout
{
    public:
        virtual ~Layout() {}
        virtual UI::Pt    getSize(std::vector<Widget> const&)    = 0;
};

class GridLayout: public Layout
{
    public:
        virtual UI::Pt    getSize(std::vector<Widget> const&);
};

struct Theme
{
};

class Widget: public UI::Sprite
{
    public:
        Widget(UI::Window& window);
        virtual ~Widget();

        // virtual void doDraw(UI::DrawContext& drawContext)   = 0;
        virtual bool doUpdateState() override {return true;}
};

class View: public Widget
{
    Layout&                 layout;
    Theme&                  theme;
    std::vector<Widget*>    widgets;
    public:
        View(Layout& layout, Theme& theme);
        virtual void doDraw(UI::DrawContext& drawContext) override;

    private:
        friend class Widget;
        void registerWidget(Widget& widget);
};
}

#endif
