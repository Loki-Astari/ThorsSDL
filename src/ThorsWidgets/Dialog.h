#ifndef THORSANVIL_WIDGETS_DIALOG_H
#define THORSANVIL_WIDGETS_DIALOG_H

#include "ThorsWidgetsConfig.h"

#include <tuple>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

template<typename T>
struct InputWidget;

template<>
struct InputWidget<std::string>
{
    using InputWidgetType = WidgetInputText;
};

template<typename T, typename A>
A& fw(A& arg)  {return arg;}

template<typename T>
struct InputLine
{
    using InputWidgetType = typename InputWidget<T>::InputWidgetType;

    WidgetLabel        label;
    InputWidgetType    input;
    InputLine(ThorsAnvil::Widgets::View& view)
        : label(view, " ")
        , input(view, " ")
    {}
    void setName(std::string const& labelValue)
    {
        label.setValue(labelValue);
    }
    T const& value() const
    {
        return input.value();
    }
};


template<typename... Args>
class Dialog
{
    using Input = std::tuple<InputLine<Args>...>;

    UI::Window          dialog;
    GridLayout          layout;
    Theme               theme;
    View                view;
    Input               input;
    WidgetLabel         blank;
    WidgetButton        button;

    public:
        template<typename... Input>
        Dialog(std::function<void(Args const&...)>&& action, Input&&... textLabels)
            : dialog("New High Score", {ThorsAnvil::UI::windowCentered, ThorsAnvil::UI::windowCentered, 0, 0}, {.hidden = true, .grabFocus = true})
            , layout(2, ThorsAnvil::Widgets::FixedHeight, ThorsAnvil::Widgets::Left, ThorsAnvil::Widgets::Top)
            , theme{}
            , view(dialog, layout, theme)
            , input(fw<Args>(view)...)
            , blank(view, " ")
            , button(view, "OK", [&dialog = this->dialog, action = std::move(action), self = this](){self->activate(action);dialog.show(false);})
        {
            addLabels(std::make_tuple(textLabels...), std::make_index_sequence<sizeof...(textLabels)>{});
            dialog.updateView(0, true);
        }
        void show()
        {
            dialog.show();
        }
        void activate(std::function<void(Args const&...)> const& action)
        {
            doActivate(action, std::make_index_sequence<sizeof...(Args)>{});
        }
    private:
        template<typename Tp, std::size_t... I>
        void addLabels(Tp&& tuple, std::index_sequence<I...>&&)
        {
            (std::get<I>(input).setName(std::get<I>(tuple)),...);
        }
        template<std::size_t... I>
        void doActivate(std::function<void(Args const&...)> const& action, std::index_sequence<I...>&&) const
        {
            action(std::get<I>(input).value()...);
        }
};

}

#endif
