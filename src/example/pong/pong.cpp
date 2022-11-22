#include "ThorsSDL/ThorsSDL.h"

namespace UI = ThorsAnvil::UI;

int main()
{
    UI::Application     application(UI::Video);
    UI::Window          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, 1280, 720}, {});

    application.eventLoop([]()
    {
        SDL_Delay(16);
    });
}
