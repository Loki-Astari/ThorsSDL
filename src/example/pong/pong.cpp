#include "ThorsSDL/ThorsSDL.h"
#include "ThorsSDL/DebugApplication.h"

namespace UI = ThorsAnvil::UI;

class PongWindow: public UI::Window
{
    UI::Pen             pen{UI::C::black, UI::C::red};
    public:
        using Window::Window;

        virtual void doDraw() override
        {
            pen.drawRect(*this, {622, 700, 36, 18});
        }
};


int main()
{
    UI::DebugApplication     application(UI::Video);
    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, 1280, 720}, {});

    application.eventLoop([]()
    {
        SDL_Delay(16);
    });
}
