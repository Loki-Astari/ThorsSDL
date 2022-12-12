#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include "View.h"
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
    //ThorsAnvil::UI::DebugWindow         window("Test Widgets", {100, 100, 200, 200});

    ThorsAnvil::Widgets::VertBoxLayout  layout(ThorsAnvil::Widgets::Center);
    //ThorsAnvil::Widgets::GridLayout     layout(3, ThorsAnvil::Widgets::Middle, ThorsAnvil::Widgets::Center);
    ThorsAnvil::Widgets::Theme          theme;
    ThorsAnvil::Widgets::View           widgetsView(window, layout, theme);

    theme.normalTextPen = ThorsAnvil::Widgets::ThemeUtility::getPen("Brush Script", 36, ThorsAnvil::UI::C::darkgrey);

    ThorsAnvil::Widgets::WidgetExample  item1(widgetsView);
    ThorsAnvil::Widgets::WidgetExample  item2(widgetsView);
    ThorsAnvil::Widgets::WidgetExample  item3(widgetsView);
    ThorsAnvil::Widgets::WidgetExample  item4(widgetsView);
    ThorsAnvil::Widgets::WidgetExample  item5(widgetsView);
    ThorsAnvil::Widgets::WidgetLabel    label(widgetsView, "This is some text");
    ThorsAnvil::Widgets::WidgetButton   button(widgetsView, "This is some text");

    widgetsView.tile();

    application.eventLoop(1000);

    std::cout << "WidgetTest\n";
}
