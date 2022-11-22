#include <iostream>
#include "ThorsSDL/ThorsSDL.h"

namespace UI = ThorsAnvil::UI;

int main()
{
    std::cout << "Pong V1\n";

    UI::Application     application;
    UI::Window          window("Pong", {10, 10, 100, 100}, UI::WindowState{.type = UI::Metal});

    SDL_Delay(20000);
}
