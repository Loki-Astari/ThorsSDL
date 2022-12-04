#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "WidgetView.h"

int main()
{
    ThorsAnvil::UI::Application         application;
    ThorsAnvil::UI::Window              window("Test Widgets", {100, 100, 200, 200});

    ThorsAnvil::Widgets::WidgetView     view;
    window.addView(view);

    application.eventLoop(1000);

    std::cout << "WidgetTest\n";
}
