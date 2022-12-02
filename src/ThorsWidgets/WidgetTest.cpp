#include "Widget.h"
#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Util.h"

int main()
{
    ThorsAnvil::UI::Application     application;
    ThorsAnvil::UI::Window          window("Widget Example v1.0", {ThorsAnvil::UI::windowUndefinedPos, ThorsAnvil::UI::windowUndefinedPos, 500, 500});

    application.eventLoop(60);
}
