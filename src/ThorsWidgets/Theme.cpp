#include "Theme.h"
#include "WidgetView.h"
#include "WidgetLabel.h"
#include "WidgetInputText.h"
#include "WidgetButton.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;

// By default we don't draw anything for a view.
void Theme::drawWidget(UI::DrawContext&, WidgetView const&) const
{}

void Theme::drawWidget(UI::DrawContext&, WidgetLabel const& label) const
{
    UI::Pt point = label.getPos();
    UI::Sz size  = label.getSize();
    label.centerText(*this, point, size);

    UI::Sz textSize = label.texture.size();
    label.texture.draw({point.x, point.y, textSize.x, textSize.y});
}

void Theme::drawWidget(UI::DrawContext& drawContext, WidgetInputText const& inputText) const
{
    UI::Pt          point   = inputText.getPos();
    UI::Sz          size    = inputText.getSize();
    UI::TextPen const&    pen     = inputNormalTextPen;

    // Draw the boarder around the text input.
    inputNormalBorderPen.drawRect(drawContext, {point.x, point.y, size.x, size.y});
    if (inputText.state != Normal) {
        inputFocusBorderPen.drawRect(drawContext, {point.x + 2, point.y + 2, size.x - 4, size.y - 4});
    }

    // Adjust the draw point to include just the text.
    inputText.centerText(*this, point, size);

    // Draw the selection
    int insertPointPixel    = pen.length(inputText.text.substr(0, inputText.insertPoint));
    if (inputText.state != Normal && inputText.insertPoint != inputText.insertEnd)
    {
        int insertEndPixel      = pen.length(inputText.text.substr(0, inputText.insertEnd));
        inputSelectedTextPen.drawRect(drawContext, {point.x + insertPointPixel, point.y, insertEndPixel - insertPointPixel, inputText.displayCharSize.y});
    }

    // Draw the flashing carot if no selection.
    if (inputText.insertPoint == inputText.insertEnd && inputText.flash)
    {
        UI::Sz caretSize = inputText.caret.size();
        inputText.caret.draw({point.x + insertPointPixel - caretSize.x / 2, point.y, caretSize.x, caretSize.y});
    }

    // Finally draw the text.
    UI::Sz textSize = inputText.textTexture.size();
    inputText.textTexture.draw({point.x, point.y, textSize.x, textSize.y});

}

void Theme::drawWidget(UI::DrawContext& drawContext, WidgetButton const& button) const
{
    UI::Pt          point   = button.getPos();
    UI::Sz          size    = button.getSize();
    UI::Pen const&  pen     = button.state != Down ? buttonBorderPen : buttonPressedPen;

    pen.drawRect(drawContext, {point.x, point.y, size.x, size.y});
    drawWidget(drawContext, static_cast<WidgetLabel const&>(button));
}
