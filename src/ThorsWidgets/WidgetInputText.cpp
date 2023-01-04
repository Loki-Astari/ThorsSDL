#include "WidgetInputText.h"
#include "Theme.h"
#include "ThorsUI/Pen.h"
#include "EventFocusKeyboard.h"

using namespace ThorsAnvil::Widgets;

WidgetInputText::WidgetInputText(WidgetView& parent,
                                 std::string const& textParam,
                                 UI::Sz minSize, bool visible)
    : Widget(parent, minSize, visible)
    , WidgetKeyboardFocusInterface(parent, [&](){return dynamic_cast<Widget&>(*this).isVisible();})
    , WidgetMouseFocusInterface(parent, [&](){return dynamic_cast<Widget&>(*this).getRect();}, [&](){return dynamic_cast<Widget&>(*this).isVisible();})
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
    markDirty();
}

UI::TextPen const& WidgetInputText::getTextPen(Theme const& theme)
{
    return theme.inputNormalTextPen;
}

void WidgetInputText::handleEventMouseUpInWidget()
{
    markDirty();
    state = state != Normal ? Focus : Normal;
}

void WidgetInputText::handleEventMouseUpOutsideWidget()
{
    markDirty();
    state = Focus;
}

void WidgetInputText::acceptKeyboardFocus()
{
    markDirty();
    state = Drag;
}

void WidgetInputText::looseKeyboardFocus()
{
    markDirty();
    state = Normal;
}

void WidgetInputText::handleEventTextInsert(Uint16 keyMod, SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_DELETE:
        case SDLK_AC_BACK:
        case SDLK_ALTERASE:
        case SDLK_BACKSPACE:
        case SDLK_KP_BACKSPACE:
            if (insertPoint != insertEnd)
            {
                text.erase(insertPoint, (insertEnd - insertPoint));
                insertEnd = insertPoint;
            }
            else
            if (insertPoint > 0)
            {
                text.erase(insertPoint - 1, 1);
                --insertPoint;
            }
            markDirty();
            break;
        case SDLK_LEFT:
            insertPoint = std::max(0, insertPoint - 1);
            if ((keyMod & KMOD_SHIFT) == 0) {
                insertEnd = insertPoint;
            }
            markDirty();
            break;
        case SDLK_RIGHT:
            insertEnd = std::min(text.size(), static_cast<std::size_t>(insertEnd + 1));
            if ((keyMod & KMOD_SHIFT) == 0) {
                insertPoint = insertEnd;
            }
            markDirty();
            break;
        case SDLK_a:
            if ((keyMod & KMOD_GUI) != 0)
            {
                insertPoint = 0;
                insertEnd   = text.size();
            }
            markDirty();
            break;
        case SDLK_TAB:
        case SDLK_KP_TAB:
            keyboardFocusWidgets.moveKeyboardFocusToNextAvailableWidget((keyMod & KMOD_SHIFT) == 0);
            markDirty();
            break;
        // TODO
        // Add Cut/Copy/Paste here.
    }
}

void WidgetInputText::handleEventTextInsert(std::string_view view)
{
    markDirty();
    if (insertPoint != insertEnd)
    {
        text.erase(insertPoint, (insertEnd - insertPoint));
        insertEnd = insertPoint;
    }
    text.insert(std::begin(text) + insertPoint, std::begin(view), std::end(view));
    insertPoint += std::size(view);
    insertEnd = insertPoint;
}

std::string const& WidgetInputText::value() const
{
    return text;
}
