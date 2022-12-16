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

int main()
{
    ThorsAnvil::UI::Application             application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Fonts);
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
    ThorsAnvil::Widgets::WidgetButton       button1(widgetsView, "Press", [](){std::cerr << "Button Pressed\n";});
    ThorsAnvil::Widgets::WidgetExample      item6(widgetsView);
    ThorsAnvil::Widgets::WidgetLabel        label2(widgetsView, "Input");
    ThorsAnvil::Widgets::WidgetInputText    input1(widgetsView, "");

    window.updateView(0, true);
    application.eventLoop(1000);

    std::cout << "WidgetTest\n";
}
