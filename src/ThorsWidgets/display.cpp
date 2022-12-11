#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "Window.h"
#include "WidgetView.h"
#include "Layout.h"
#include "Theme.h"
#include "WidgetExample.h"

int main()
{
    ThorsAnvil::UI::Application         application;
    ThorsAnvil::UI::Window              window("Test Widgets", {100, 100, 200, 200});

    ThorsAnvil::Widgets::VertBoxLayout    layout(ThorsAnvil::Widgets::Center);
    //ThorsAnvil::Widgets::GridLayout     layout(3, ThorsAnvil::Widgets::Middle, ThorsAnvil::Widgets::Center);
    ThorsAnvil::Widgets::Theme          theme;
    ThorsAnvil::Widgets::Window         widgetWindow(layout, theme);
    window.addView(widgetWindow);

    ThorsAnvil::Widgets::WidgetExample  item1(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item2(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item3(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item4(widgetWindow);
    ThorsAnvil::Widgets::WidgetExample  item5(widgetWindow);

    widgetWindow.tile();

    application.eventLoop(1000);

    std::cout << "WidgetTest\n";
}
