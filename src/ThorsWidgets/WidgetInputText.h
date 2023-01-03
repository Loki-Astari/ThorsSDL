#ifndef THORSANVIL_WIDGETS_WIDGET_INPUT_TEXT_H
#define THORSANVIL_WIDGETS_WIDGET_INPUT_TEXT_H

/*
 * An Input Widget for handling Text Input
 */

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include "KeyboardFocusSet.h"
#include "ThorsUI/Texture.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

enum InputTextState {Normal, Focus, Drag};

struct Theme;
class WidgetInputText: public Widget, public WidgetKeyboardFocusInterface
{
    friend struct Theme;
    UI::Texture     textTexture;
    UI::Texture     caret;
    std::string     text;
    int             insertPoint;
    int             insertEnd;
    UI::Sz          displayCharSize;
    InputTextState  state;
    bool            flash;
    public:
        WidgetInputText(WidgetView& parent, std::string const& text,
                        UI::Sz minSize = {0, 0}, bool visible = true);

        std::string const& value() const;

    private:
        // Drawing the button: Delegates the theme.
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;
        // Utility class for choosing pen
        virtual UI::TextPen const&    getTextPen(Theme const& theme);

    private:
        // Handle layout.
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        // Utility class for helping in layout.
        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const;

    private:
        // Handle mouse clicks text input events:w
        virtual Widget* handleEventMouseDownInWidget() override;
        virtual Widget* handleEventMouseUpInWidget(Widget* mouseDownIn) override;
        virtual void    handleEventMouseUpOutsideWidget() override;
        virtual void    handleEventTextInsert(Uint16 keyMod, SDL_Keycode key) override;
        virtual void    handleEventTextInsert(std::string_view view) override;

        // Override for Interface WidgetKeyboardFocusInterface
        virtual void    acceptKeyboardFocus() override;
        virtual void    looseKeyboardFocus() override;
};

}

#endif
