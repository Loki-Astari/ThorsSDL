#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include "LayoutUtil.h"
#include "View.h"
#include "WidgetView.h"
#include "Layout.h"
#include "Theme.h"
#include "WidgetExample.h"
#include "WidgetLabel.h"
#include "WidgetInputText.h"
#include "WidgetButton.h"
#include <tuple>

template<typename T>
struct InputWidget;

template<>
struct InputWidget<std::string>
{
    using InputWidgetType = ThorsAnvil::Widgets::WidgetInputText;
};

template<typename T, typename A>
A& fw(A& arg)  {return arg;}

template<typename T>
struct InputLine
{
    using InputWidgetType = typename InputWidget<T>::InputWidgetType;

    ThorsAnvil::Widgets::WidgetLabel        label;
    InputWidgetType                         input;
    InputLine(ThorsAnvil::Widgets::View& view)//, std::string const& l)
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
    ThorsAnvil::UI::Window                  dialog;
    ThorsAnvil::Widgets::GridLayout         layout;
    ThorsAnvil::Widgets::Theme              theme;
    ThorsAnvil::Widgets::View               view;
    std::tuple<InputLine<Args>...>          input;
    ThorsAnvil::Widgets::WidgetLabel        blank;
    ThorsAnvil::Widgets::WidgetButton       button;

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

class DialogNameAge: public Dialog<std::string, std::string>
{
    public:
        DialogNameAge(std::function<void(std::string const&, std::string const&)>&& action)
            : Dialog(std::move(action), "Name: ", "Age: ")
        {}
};

int main()
{
    ThorsAnvil::UI::Application             application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Fonts);
    DialogNameAge                           dialog([](std::string const& p, std::string const& x){std::cerr << p << " " << x << "\n";});
    ThorsAnvil::UI::Window                  window("Test Widgets", {100, 100, 200, 200});
    //ThorsAnvil::UI::DebugWindow             window("Test Widgets", {100, 100, 200, 200});

    //ThorsAnvil::Widgets::VertBoxLayout      layout(ThorsAnvil::Widgets::Center);
    ThorsAnvil::Widgets::GridLayout         layout(2, ThorsAnvil::Widgets::FixedHeight, ThorsAnvil::Widgets::Left, ThorsAnvil::Widgets::Top);
    ThorsAnvil::Widgets::Theme              theme;
    ThorsAnvil::Widgets::View               widgetsView(window, layout, theme);

    ThorsAnvil::Widgets::WidgetExample      item1(widgetsView);
    ThorsAnvil::Widgets::WidgetExample      item2(widgetsView);
    ThorsAnvil::Widgets::WidgetExample      item3(widgetsView);
    ThorsAnvil::Widgets::WidgetExample      item4(widgetsView);
    ThorsAnvil::Widgets::WidgetExample      item5(widgetsView);
    ThorsAnvil::Widgets::WidgetLabel        label1(widgetsView, "This is some text");
    ThorsAnvil::Widgets::WidgetButton       button1(widgetsView, "Press", [&dialog](){dialog.show();});
    ThorsAnvil::Widgets::WidgetExample      item6(widgetsView);
    ThorsAnvil::Widgets::WidgetLabel        label2(widgetsView, "Input");
    ThorsAnvil::Widgets::WidgetInputText    input1(widgetsView, "");
    ThorsAnvil::Widgets::WidgetLabel        label3(widgetsView, "Label");
    ThorsAnvil::Widgets::WidgetInputText    input2(widgetsView, "");
    //Dialog                                  dialog2;
    //dialog2.show();

    window.updateView(0, true);
    SDL_StartTextInput();
    application.eventLoop(1000);
    SDL_StopTextInput();

    std::cout << "WidgetTest\n";
}
