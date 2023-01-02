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

        void setValue(std::string const& labelValue);
    private:
        // Drawing the button: Delegates the theme.
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme) override;

    private:
        // Layout the Label
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size) override;

        // Utility: The pen used to draw the text on the label.
        //          For a label there is only one pen.
        //          But this is overridden for other classes that use the label
        //          text drawing abilities.
        virtual UI::TextPen const&    getTextPen(Theme const& theme);

        // Utility to handle offset around pen.
        // These values extracted from Theme
        virtual UI::Sz  addOffset(Theme const& theme, UI::Sz size) const;
        virtual void    centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const;

};


}

#endif
