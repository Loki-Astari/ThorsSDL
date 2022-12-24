#ifndef THORSANVIL_WIDGETS_VIEW_H
#define THORSANVIL_WIDGETS_VIEW_H

#include "ThorsWidgetsConfig.h"
#include "LayoutUtil.h"
#include "WidgetView.h"
#include "Theme.h"
#include "WidgetKeyboardFocusI.h"
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
    Theme&              theme;
    UI::Sz              minSize;
    Widget*             mouseDownIn;
    HorzAlign           hAlign;
    VertAlign           vAlign;
    KeyboardFocusSet    textInputSet;
    bool                updated;

    public:
        View(UI::Window& window, Layout& layout, Theme& theme, UI::Sz minSize = {0, 0}, HorzAlign hAlign = Middle, VertAlign vAlign = Center);
        UI::Sz tile(bool fitWindowToView);

        virtual bool updateState() override;
        virtual void markDirty() override;
        virtual void draw(UI::DrawContext& context) override;
        virtual UI::Sz reset(bool fitWindowToView) override;

        // Mouse Handling
        virtual void handleEventWindowEnter(SDL_WindowEvent const& event) override;
        virtual void handleEventWindowLeave(SDL_WindowEvent const& event) override;
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event) override;
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& event) override;
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& event) override;

        // Text Handling
    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& /*event*/) override                {}
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& event) override;
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& /*event*/) override;
        virtual void handleEventTextInput(SDL_TextInputEvent const& /*event*/) override;
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& /*event*/) override;

        virtual KeyboardFocusSet& getInterfaceSet() override;
};

}

#endif
