#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "Window.h"
#include "WidgetView.h"
#include "Layout.h"
#include "Theme.h"
#include "WidgetExample.h"
#include "WidgetLabel.h"
#include "WidgetButton.h"

int main()
{
    ThorsAnvil::UI::Application         application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Fonts);
    ThorsAnvil::UI::Window              window("Test Widgets", {100, 100, 200, 200});

    ThorsAnvil::Widgets::VertBoxLayout    layout(ThorsAnvil::Widgets::Center);
    //ThorsAnvil::Widgets::GridLayout     layout(3, ThorsAnvil::Widgets::Middle, ThorsAnvil::Widgets::Center);
    ThorsAnvil::Widgets::Theme          theme;
    ThorsAnvil::Widgets::Window         widgetWindow(window, layout, theme);

    ThorsAnvil::Widgets::WidgetExample  item1(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item2(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item3(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item4(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item5(widgetWindow);
    ThorsAnvil::Widgets::WidgetLabel    label(widgetWindow, "This is some text", "Brush Script", 36, ThorsAnvil::UI::C::darkgrey);
    ThorsAnvil::Widgets::WidgetButton   button(widgetWindow, "This is some text", "Brush Script", 36, ThorsAnvil::UI::C::darkgrey);

    widgetWindow.tile();

    application.eventLoop(1000);

    std::cout << "WidgetTest\n";
}
