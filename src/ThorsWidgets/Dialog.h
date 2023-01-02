#ifndef THORSANVIL_WIDGETS_DIALOG_H
#define THORSANVIL_WIDGETS_DIALOG_H

/*
 * Class Dialog
 *      Displays a dialog.
 *      When "OK" button pressed calls callback function with all user requested data.
 *
 * Usage:
 *      Dialog<std::string, int>        dialog("Name: ", "Age: ");
 *      dialog.show([](std::string const& name, int const& age) {std::cout << name << " " << age << "\n";});
 *
 * Internal Types:
 *      InputLine       Builds a label and input widget for each type.
 *      InputWidget<T>::InputWidgetType     Widget type displayed by Dialog for type T user input.
 */

#include "ThorsWidgetsConfig.h"
#include "WidgetInputText.h"
#include "ThorsUI/Window.h"

#include <tuple>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

namespace Util
{
    /*
     * InputWidget: Internally used by DialogLine only.
     * Note: Only defined for std::string (expect more in the future)
     */
    template<typename T>
    struct InputWidget;

    template<>
    struct InputWidget<std::string>
    {
        using InputWidgetType = WidgetInputText;
    };

    /*
     * A group of two widgets:
     * A label and an input widget to get user input for type T
     */
    template<typename T>
    struct DialogLine
    {
        using InputWidgetType = typename InputWidget<T>::InputWidgetType;

        WidgetLabel        label;
        InputWidgetType    input;
        DialogLine(ThorsAnvil::Widgets::View& view)
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

    /*
     * Utility class to forward single argument to multiple template arguments.
     */
    template<typename T, typename A>
    A& fw(A& arg)  {return arg;}
}

template<typename... Args>
class Dialog
{
    using CallBack = std::function<void(Args const&...)>;
    using Input = std::tuple<Util::DialogLine<Args>...>;

    UI::Window          dialog;
    CallBack            callback;
    GridLayout          layout;
    Theme               theme;
    View                view;
    Input               input;
    WidgetLabel         blank;
    WidgetButton        button;

    public:
        template<typename... Request>
        Dialog(Request&&... textLabels)
            : dialog("New High Score", {ThorsAnvil::UI::windowCentered, ThorsAnvil::UI::windowCentered, 0, 0}, {.hidden = true, .grabFocus = true})
            , callback()
            , layout(2, ThorsAnvil::Widgets::FixedHeight, ThorsAnvil::Widgets::Left, ThorsAnvil::Widgets::Top)
            , theme{}
            , view(dialog, layout, theme)
            , input(Util::fw<Args>(view)...)
            , blank(view, " ")
            , button(view, "OK", [&](){activate();})
        {
            addLabels(std::make_tuple(textLabels...), std::make_index_sequence<sizeof...(textLabels)>{});
            dialog.updateView(0, true);
        }
        void show(CallBack&& newAction)
        {
            callback = std::move(newAction);
            dialog.enableTextInput(true);
            dialog.show();
        }
        void activate()
        {
            doActivate(std::make_index_sequence<sizeof...(Args)>{});
            dialog.show(false);
            dialog.enableTextInput(false);
        }
    private:
        template<typename Tp, std::size_t... I>
        void addLabels(Tp&& tuple, std::index_sequence<I...>&&)
        {
            (std::get<I>(input).setName(std::get<I>(tuple)),...);
        }
        template<std::size_t... I>
        void doActivate(std::index_sequence<I...>&&) const
        {
            callback(std::get<I>(input).value()...);
        }
};

}

#endif
