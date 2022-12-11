#ifndef THORSANVIL_WIDGETS_WIDGET_LABEL_H
#define THORSANVIL_WIDGETS_WIDGET_LABEL_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include "ThorsSDL/Texture.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class WidgetLabel: public Widget
{
    friend struct Theme;
    UI::Texture     texture;
    std::string     text;
    std::string     font;
    int             point;
    UI::Color       color;
    public:
        WidgetLabel(WidgetView& parent,
                    std::string const& text,
                    std::string const& font = "Arial", int point = 12,
                    UI::Color color = UI::C::white,
                    UI::Sz minSize = {0, 0}, bool visible = true);

        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const;
};

}

#endif
