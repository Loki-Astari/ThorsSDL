#ifndef THORSANVIL_WIDGETS_VIEW_H
#define THORSANVIL_WIDGETS_VIEW_H

#include "ThorsWidgetsConfig.h"
#include "LayoutUtil.h"
#include "WidgetView.h"
#include "Theme.h"
#include "ThorsUI/View.h"

namespace ThorsAnvil::UI
{
    class Window;
}

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class Layout;
class View: public WidgetView, public UI::View
{
    Theme&          theme;
    UI::Sz          minSize;
    Widget*         mouseDownIn;
    Widget*         textFocus;
    HorzAlign       hAlign;
    VertAlign       vAlign;

    public:
        View(UI::Window& window, Layout& layout, Theme& theme, UI::Sz minSize = {0, 0}, HorzAlign hAlign = Middle, VertAlign vAlign = Center);
        UI::Sz tile(bool fitWindowToView);

        virtual void draw(UI::DrawContext& context) override;
        virtual UI::Sz reset(bool fitWindowToView) override;

        virtual void handleEventWindowEnter(SDL_WindowEvent const& event) override;
        virtual void handleEventWindowLeave(SDL_WindowEvent const& event) override;
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event) override;
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& event) override;
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& event) override;
};

}

#endif
