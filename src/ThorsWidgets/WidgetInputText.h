#ifndef THORSANVIL_WIDGETS_WIDGET_INPUT_TEXT_H
#define THORSANVIL_WIDGETS_WIDGET_INPUT_TEXT_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include "WidgetKeyboardFocusI.h"
#include "ThorsUI/Texture.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

enum InputTextState {Normal, Focus, Drag};

struct Theme;
class WidgetInputText: public WidgetKeyboardFocusInterface
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

        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const;

        virtual UI::TextPen const&    getTextPen(Theme const& theme);

        virtual Widget* handleEventMouseDownInWidget() override;
        virtual Widget* handleEventMouseUpInWidget(Widget* mouseDownIn) override;
        virtual void    handleEventMouseUpOutsideWidget() override;
        virtual void    handleEventTextInsert(Uint16 keyMod, SDL_Keycode key) override;
        virtual void    handleEventTextInsert(std::string_view view) override;

        virtual void    acceptKeyboardFocus() override;
        virtual void    looseKeyboardFocus() override;

        std::string const& value() const;
};

}

#endif
