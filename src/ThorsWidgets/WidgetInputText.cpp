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
    , insertPoint(text.size())
    , insertEnd(insertPoint)
    , displayCharSize{0, 0}
    , state(Normal)
    , flash(false)
{}

UI::Sz WidgetInputText::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz /*size*/)
{
    if (displayCharSize.x == 0)
    {
        caret = getTextPen(theme).createTextureFromString(drawContext, "‸");
        displayCharSize.y = getTextPen(theme).lineSkip();
        displayCharSize.x = getTextPen(theme).height() * 20;
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

    textTexture = getTextPen(theme).createTextureFromString(drawContext, text.empty() ? " " : text);

    theme.drawWidget(drawContext, *this);
}

UI::TextPen const& WidgetInputText::getTextPen(Theme const& theme)
{
    return theme.inputNormalTextPen;
}

Widget* WidgetInputText::handleEventMouseDownInWidget()
{
    return this;
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

void WidgetInputText::looseTextFocus()
{
    state = Normal;
}

void WidgetInputText::handleEventTextInsert(Uint16 keyMod, SDL_Keycode key)
{
/*
        <NoMod> : <Shift> : <Ctrl>                      : <Opt>                         : <Command>
    a   4:97:0    4:97:1    225:1073742049:0 - 4:97:64    224:1073742048:0 - 4:97-256     226:1073742050:0 - 4:97:1024

    1   30:49:0 : 30:49:1   225:1073742049:0 - 30:49:64   224:1073742048:0 - 30:49:256    226:1073742050:0 - 30:49:?

225 1073742049 => bit(30) + 225     0x400000E1  SDLK_LSHIFT <SHIFT>
224 1073742048 => bit(30) + 224     0x400000E0  SDLK_LCTRL  <CTRL>
226 1073742050 => bit(30) + 226     0x400000E2  SDLK_LALT   <ALT>
227 1073742051 => bit(30) + 227     0x400000E3  SDLK_LGUI   <CMD>
*/
    std::cerr << "Key: " << key << "\n";
    switch (key)
    {
        case SDLK_DELETE:
        case SDLK_AC_BACK:
        case SDLK_ALTERASE:
        case SDLK_BACKSPACE:
        case SDLK_KP_BACKSPACE:
            if (insertPoint > 0)
            {
                text.erase(insertPoint - 1, 1);
                --insertPoint;
            }
            break;
        case SDLK_LEFT:
            insertPoint = std::max(0, insertPoint - 1);
            if ((keyMod & KMOD_SHIFT) == 0) {
                insertEnd = insertPoint;
            }
            break;
        case SDLK_RIGHT:
            insertEnd = std::min(text.size(), static_cast<std::size_t>(insertEnd + 1));
            if ((keyMod & KMOD_SHIFT) == 0) {
                insertPoint = insertEnd;
            }
            break;
    }
}

void WidgetInputText::handleEventTextInsert(std::string_view view)
{
    if (insertPoint != insertEnd)
    {
        text.erase(insertPoint, (insertEnd - insertPoint));
        insertEnd = insertPoint;
    }
    text.insert(std::begin(text) + insertPoint, std::begin(view), std::end(view));
    insertPoint += std::size(view);
    insertEnd = insertPoint;
}
