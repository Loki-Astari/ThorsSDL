#include "ThorsSDL/ThorsSDL.h"

namespace UI = ThorsAnvil::UI;

int main()
{
    UI::Application     application(UI::Video);
    UI::Window          window(application, "Pong v1.0", {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720}, {});

    application.eventLoop([]()
    {
        SDL_Delay(16);
    });
}
