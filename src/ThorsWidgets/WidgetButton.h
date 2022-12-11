#ifndef THORSANVIL_WIDGETS_WIDGET_BUTTON_H
#define THORSANVIL_WIDGETS_WIDGET_BUTTON_H

#include "ThorsWidgetsConfig.h"
#include "WidgetLabel.h"
#include "ThorsSDL/Texture.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class WidgetButton: public WidgetLabel
{
    public:
        using WidgetLabel::WidgetLabel;

        //virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const override;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const override;
};

}

#endif
