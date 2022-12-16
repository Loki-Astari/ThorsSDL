#include "WidgetInputText.h"
#include "Theme.h"
#include "ThorsUI/Pen.h"
#include <chrono>

using namespace ThorsAnvil::Widgets;

WidgetInputText::WidgetInputText(WidgetView& parent,
                                 std::string const& textParam,
                                 UI::Sz minSize, bool visible)
    : Widget(parent, minSize, visible)
    , text(textParam)
    , displayCharSize{0, 0}
    , state(Normal)
    , flash(false)
{}

UI::Sz WidgetInputText::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz /*size*/)
{
    if (displayCharSize.x == 0)
    {
        // std::cerr << "Creating Blank Surface\n";
        UI::Texture blankSize = getTextPen(theme).createTextureFromString(drawContext, "M");
        // std::cerr << "Creating Blank Surface DONE\n";
        displayCharSize = blankSize.size();
        displayCharSize.x *= 20;
    }
    return addOffset(theme, displayCharSize);
}

UI::Sz WidgetInputText::addOffset(Theme const& theme, UI::Sz size) const
{
    size.x += theme.inputTextBorder.x + theme.inputTextBorder.w;
    size.y += theme.inputTextBorder.y + theme.inputTextBorder.h;
    return size;
}

void WidgetInputText::centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const
{
    topLeft.x += theme.inputTextBorder.x;
    topLeft.y += theme.inputTextBorder.y;

    size.x    -= (theme.inputTextBorder.x + theme.inputTextBorder.w);
    size.y    -= (theme.inputTextBorder.y + theme.inputTextBorder.h);
}

void WidgetInputText::drawWidget(UI::DrawContext& drawContext, Theme const& theme)
{
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    static TimePoint    lastUpdate  = std::chrono::system_clock::now();

    if (state != Normal)
    {
        TimePoint thisTime = std::chrono::system_clock::now();
        int timeout = flash ? 800 : 400;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(thisTime - lastUpdate).count() > timeout)
        {
            lastUpdate = thisTime;
            flash = !flash;
        }
    }
    else
    {
        flash = false;
    }

    std::string localText = text + (flash ? "‸" : " ");
    texture = getTextPen(theme).createTextureFromString(drawContext, localText);

    theme.drawWidget(drawContext, *this);
}

UI::TextPen const& WidgetInputText::getTextPen(Theme const& theme)
{
    return theme.inputNormalTextPen;
}

Widget* WidgetInputText::handleEventMouseDownInWidget()
{
    return this;;
}

Widget* WidgetInputText::handleEventMouseUpInWidget(Widget* /*mouseDownIn*/)
{
    state = state != Normal ? Focus : Normal;
    return nullptr;
}

void WidgetInputText::handleEventMouseUpOutsideWidget()
{
    state = Focus;
}

Widget* WidgetInputText::acceptTextFocus()
{
    state = Drag;
    return this;
}

void WidgetInputText::looseFocus()
{
    state = Normal;
}
