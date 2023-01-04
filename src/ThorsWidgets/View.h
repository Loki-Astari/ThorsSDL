#ifndef THORSANVIL_WIDGETS_VIEW_H
#define THORSANVIL_WIDGETS_VIEW_H

/*
 * View:        Basic override of ThorsUI::View
 *              Add an object of this type to a window. This object can then hold multiple
 *              Widgets that each know how to draw themselves and interact with the user.
 *
 * Note:        This object is also a WidgetView.
 *              To allow it to layout out its children.
 *
 * This object redirect events to the appropriate Widget so they can be handled.
 * Tracks two major things:
 *      mouseDownIn:            The mouse was clicked in this widget.
 *                              All subsequent mouse events will be passed to this widget for processing.
 *                              Note 1: by default this is nullptr
 *                              Note 2: Mouse down followed by Mouse up not in the same element will set it to nullptr.
 *      EventFocusKeyboard:     This object handles keyboard events.
 *                              It will track all controls that can accept keyboard focus and track the change in keyboard
 *                              focus.
 */

#include "ThorsWidgetsConfig.h"
#include "LayoutUtil.h"
#include "WidgetView.h"
#include "Theme.h"
#include "EventFocusKeyboard.h"
#include "EventFocusMouse.h"
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
    //Widget*             mouseDownIn;
    HorzAlign           hAlign;
    VertAlign           vAlign;
    EventFocusKeyboard  textInputSet;
    EventFocusMouse     mouseInputSet;
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
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& event) override;
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& event) override;
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& event) override;
        virtual void handleEventTextInput(SDL_TextInputEvent const& event) override;
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event) override;

        virtual EventFocusKeyboard&   getKeyboardInterfaceSet() override;
        virtual EventFocusMouse&      getMouseInterfaceSet() override;
};

}

#endif
