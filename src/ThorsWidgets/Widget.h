#ifndef THORSANVIL_WIDGETS_WIDGET_H
#define THORSANVIL_WIDGETS_WIDGET_H

/*
 * Widget:      Virtual base class to all widgets
 */

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

enum WidgetType {Unknown, Label};

class Layout;
class WidgetView;
struct Theme;
class KeyboardFocusSet;
class MouseFocusSet;

class Widget
{
    WidgetView*         parentWidget;
    UI::Pt              topLeft;
    UI::Sz              size;
    UI::Sz              minSize;
    UI::TimePoint       lastUpdate;
    bool                visible;

    public:
        Widget(UI::Sz minSize, bool visible = true);
        Widget(WidgetView& parentWidget, UI::Sz minSize, bool visible = true);
        virtual ~Widget();

                UI::Pt const&       getPos()    const   {return topLeft;}
                UI::Sz const&       getSize()   const   {return size;}
                UI::Rect            getRect()   const   {return {topLeft.x, topLeft.y, size.x, size.y};}
                bool                isVisible() const   {return visible;}
        virtual void                markDirty();

    private:
        friend class View;
        friend class WidgetView;
        // Each Widget can handle its own drawing.
        // This is called by the parentWidget (which may be the View).
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)    = 0;

    private:
        // The Layout class handles all the layout stuff to do with Widgets.
        friend class Layout;
        friend class GroupLayout;
        // Handle Layout
                UI::Sz  preferredLayout(UI::DrawContext& context, Theme const& theme);
                void    performLayout(UI::Pt newTopLeft, Theme const& theme);
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size);
        virtual void    doPerformLayout(UI::Pt newTopLeft, Theme const& theme);
        // Utility functions to help in layout.
        virtual WidgetType          type()      const   {return Unknown;}

    private:
        // Utility for handling keyboard focus.
        friend class KeyboardFocusSet;
        friend class WidgetKeyboardFocusInterface;
        friend class WidgetMouseFocusInterface;
        virtual KeyboardFocusSet&   getKeyboardInterfaceSet();
        virtual MouseFocusSet&      getMouseInterfaceSet();

};

/*
 * A Widget that accepts Keyboard Focus
 */
class WidgetKeyboardFocusInterface
{
    protected:
        KeyboardFocusSet&           keyboardFocusWidgets;
        std::function<bool()>       iVis;
    public:
        WidgetKeyboardFocusInterface(WidgetView& parentWidget, std::function<bool()>&& iVis);
        virtual ~WidgetKeyboardFocusInterface();

        virtual void    acceptKeyboardFocus() = 0;
        virtual void    looseKeyboardFocus()  = 0;
                bool    isVisible() const   {return iVis();}

        virtual void    handleEventTextInsert(Uint16 keyMod, SDL_Keycode key)   = 0;
        virtual void    handleEventTextInsert(std::string_view view)            = 0;
};

class WidgetMouseFocusInterface
{
    protected:
        MouseFocusSet&              mouseFocusWidgets;
        std::function<UI::Rect()>   gRect;
        std::function<bool()>       iVis;
    public:
        WidgetMouseFocusInterface(WidgetView& parentWidget, std::function<UI::Rect()>&& geRect, std::function<bool()>&& iVis);
        virtual ~WidgetMouseFocusInterface();

                bool        isVisible() const   {return iVis();}
                UI::Rect    getRect() const     {return gRect();}

        virtual void    handleEventMouseMoveInWidget()                          = 0;

        virtual void    handleEventMouseMoveEnterWidget()                       = 0;
        virtual void    handleEventMouseMoveLeaveWidget()                       = 0;
        virtual void    handleEventMouseDownInWidget()                          = 0;
        virtual void    handleEventMouseUpInWidget()                            = 0;
        virtual void    handleEventMouseUpOutsideWidget()                       = 0;
};

}

#endif
