#ifndef THORSANVIL_WIDGETS_WIDGET_BUTTON_H
#define THORSANVIL_WIDGETS_WIDGET_BUTTON_H

#include "ThorsWidgetsConfig.h"
#include "WidgetLabel.h"
#include "ThorsUI/Texture.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class WidgetButton: public WidgetLabel
{
    friend struct Theme;
    bool    mouseInButton   = false;

    public:
        using WidgetLabel::WidgetLabel;

        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const override;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const override;
        virtual void    handleEventMouseMoveEnterWidget() override;
        virtual void    handleEventMouseMoveLeaveWidget() override;

        virtual UI::TextPen const& getTextPen(Theme const& theme) override;
};

}

#endif
