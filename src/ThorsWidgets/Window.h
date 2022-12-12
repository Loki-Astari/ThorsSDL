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

        virtual void handleEventWindowEnter(SDL_WindowEvent const& event) override;
        virtual void handleEventWindowLeave(SDL_WindowEvent const& event) override;
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event) override;
};

}

#endif
