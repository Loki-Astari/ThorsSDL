#ifndef THORSANVIL_WIDGETS_WIDGET_LABEL_H
#define THORSANVIL_WIDGETS_WIDGET_LABEL_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include "ThorsUI/Texture.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

struct Theme;
class WidgetLabel: public Widget
{
    friend struct Theme;
    UI::Texture     texture;
    std::string     text;
    public:
        WidgetLabel(WidgetView& parent, std::string const& text,
                    UI::Sz minSize = {0, 0}, bool visible = true);

        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const;

        virtual UI::TextPen const&    getTextPen(Theme const& theme);
};

}

#endif
