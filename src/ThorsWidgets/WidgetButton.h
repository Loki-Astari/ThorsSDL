#ifndef THORSANVIL_WIDGETS_WIDGET_BUTTON_H
#define THORSANVIL_WIDGETS_WIDGET_BUTTON_H

#include "ThorsWidgetsConfig.h"
#include "WidgetLabel.h"
#include "ThorsUI/Texture.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

enum ButtonState {Up, Hover, Down, DownOutside};
using ButtonAction = std::function<void()>;

struct Theme;
class WidgetButton: public WidgetLabel
{
    friend struct Theme;
    ButtonState     state   = Up;
    ButtonAction    action;

    public:
        WidgetButton(WidgetView& parent, std::string const& text,
                     ButtonAction&& action = [](){},
                     UI::Sz minSize = {0, 0}, bool visible = true);

    private:
        // Drawing the button: Delegates the theme.
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

    private:
        // Handle mouse clicks on the button.
        virtual void    handleEventMouseMoveEnterWidget() override;
        virtual void    handleEventMouseMoveLeaveWidget() override;
        virtual Widget* handleEventMouseDownInWidget() override;
        virtual Widget* handleEventMouseUpInWidget(Widget* mouseDownIn) override;
        virtual void    handleEventMouseUpOutsideWidget() override;

    private:
        // Utility: The pen used to draw the text on the button.
        //          This differs depending on state.
        virtual UI::TextPen const& getTextPen(Theme const& theme) override;

        // Utility to handle offset around pen.
        // These values extracted from Theme
        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const override;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const override;
};

}

#endif
