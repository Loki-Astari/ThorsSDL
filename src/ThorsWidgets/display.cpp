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

class Dialog
{
    ThorsAnvil::UI::Window                  dialog;
    ThorsAnvil::Widgets::GridLayout         layout;
    ThorsAnvil::Widgets::Theme              theme;
    ThorsAnvil::Widgets::View               view;
    ThorsAnvil::Widgets::WidgetLabel        label;
    ThorsAnvil::Widgets::WidgetInputText    input;
    ThorsAnvil::Widgets::WidgetLabel        blank;
    ThorsAnvil::Widgets::WidgetButton       button;

    public:
        Dialog()
            : dialog("New High Score", {ThorsAnvil::UI::windowCentered, ThorsAnvil::UI::windowCentered, 0, 0}, {.hidden = true, .grabFocus = true})
            , layout(2, ThorsAnvil::Widgets::FixedHeight, ThorsAnvil::Widgets::Left, ThorsAnvil::Widgets::Top)
            , theme{}
            , view(dialog, layout, theme)
            , label(view, "Name: ")
            , input(view, "")
            , blank(view, " ")
            , button(view, "OK", [&dialog = this->dialog](){dialog.show(false);})
        {
            dialog.updateView(0, true);
        }
        void show()
        {
            dialog.show();
        }
};

int main()
{
    ThorsAnvil::UI::Application             application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Fonts);
    Dialog                                  dialog;
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
    Dialog                                  dialog2;
    dialog2.show();

    window.updateView(0, true);
    SDL_StartTextInput();
    application.eventLoop(1000);
    SDL_StopTextInput();

    std::cout << "WidgetTest\n";
}
