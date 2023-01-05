#include "FocusTrackerKeyboard.h"
#include "ControleHandlerKeyboard.h"
#include "Widget.h"

using namespace ThorsAnvil::Widgets;


FocusTrackerKeyboard::FocusTrackerKeyboard()
    : current(std::end(textInputWidgets))
{}

void FocusTrackerKeyboard::handleEventMouseDown(Widget& mouseDownIn)
{
    ControleHandlerKeyboard*  keyboardFocus = dynamic_cast<ControleHandlerKeyboard*>(&mouseDownIn);
    if (keyboardFocus)
    {
        if (current != std::end(textInputWidgets)) {
            (*current)->handleEventTextLoseFocus();
        }
        current = std::find(std::begin(textInputWidgets), std::end(textInputWidgets), keyboardFocus);
        keyboardFocus->handleEventTextGainFocus();
    }
}

void FocusTrackerKeyboard::handleEventKeyDown(SDL_KeyboardEvent const& /*event*/)
{}

void FocusTrackerKeyboard::handleEventKeyUp(SDL_KeyboardEvent const& event)
{
    if (current != std::end(textInputWidgets)) {
        (*current)->handleEventTextInsert(event.keysym.mod, event.keysym.sym);
    }
}

void FocusTrackerKeyboard::handleEventTextEditting(SDL_TextEditingEvent const& event)
{
    if (current != std::end(textInputWidgets)) {
        (*current)->handleEventTextInsert(std::string_view(event.text + event.start, event.length));
    }
}

void FocusTrackerKeyboard::handleEventTextInput(SDL_TextInputEvent const& event)
{
    if (current != std::end(textInputWidgets)) {
        (*current)->handleEventTextInsert(std::string_view(event.text));
    }
}

void FocusTrackerKeyboard::handleEventTextEditingExt(SDL_TextEditingExtEvent const& event)
{
    if (current != std::end(textInputWidgets)) {
        (*current)->handleEventTextInsert(std::string_view(event.text + event.start, event.length));
    }
}

void FocusTrackerKeyboard::addInterface(ControleHandlerKeyboard& interface)
{
    textInputWidgets.emplace_back(&interface);

    if (current == std::end(textInputWidgets)) {
        current = std::begin(textInputWidgets);
    }
}

void FocusTrackerKeyboard::remInterface(ControleHandlerKeyboard& interface)
{
    auto find = std::find(std::begin(textInputWidgets), std::end(textInputWidgets), &interface);
    if (find == current)
    {
        current = findNextWidget(true);
        if (find == current) {
            current = std::end(textInputWidgets);
        }
        if (current != std::end(textInputWidgets)) {
            (*current)->handleEventTextGainFocus();
        }
    }
    if (find != std::end(textInputWidgets)) {
        textInputWidgets.erase(find);
    }
}

void FocusTrackerKeyboard::reset()
{
    if (current != std::end(textInputWidgets)) {
        (*current)->handleEventTextGainFocus();
    }
}

void FocusTrackerKeyboard::moveKeyboardFocusToNextAvailableWidget(bool forward)
{
    Iterator next = findNextWidget(forward);
    if (next != current)
    {
        if (current != std::end(textInputWidgets)) {
            (*current)->handleEventTextLoseFocus();
        }
        current = next;
        if (current != std::end(textInputWidgets)) {
            (*current)->handleEventTextGainFocus();
        }
    }
}

FocusTrackerKeyboard::Iterator FocusTrackerKeyboard::findNextWidget(bool forward)
{
    if (textInputWidgets.empty()) {
        return std::end(textInputWidgets);
    }

    if (forward)
    {
        auto find = std::find_if(std::next(current), std::end(textInputWidgets), [](auto iter){return iter->isVisible();});
        if (find == std::end(textInputWidgets)) {
             find = std::find_if(std::begin(textInputWidgets), current, [](auto iter){return iter->isVisible();});
        }
        return find;
    }
    else
    {
        auto find = std::find_if(std::reverse_iterator(current), std::reverse_iterator(std::begin(textInputWidgets)), [](auto iter){return iter->isVisible();});
        if (find.base() == std::begin(textInputWidgets)) {
            find = std::find_if(std::reverse_iterator(std::end(textInputWidgets)), std::reverse_iterator(std::next(current)), [](auto iter){return iter->isVisible();});
        }
        return std::prev(find.base());
    }
}
