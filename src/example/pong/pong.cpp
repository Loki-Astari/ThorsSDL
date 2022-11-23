#include "ThorsSDL/ThorsSDL.h"
#include "ThorsSDL/DebugApplication.h"

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    class Paddle
    {
        int const   speed           = 20;
        int const   height          = 18;
        int const   width           = 36;
        int const   border          = 4;
        UI::Pen     pen{UI::C::black, UI::C::red};
        int         pos;
        int         base;
        public:
            Paddle(int middle, int bottom)
                : pos(middle - (width / 2))
                , base(bottom - height - border)
            {}
            void draw(Window& window)   { pen.drawRect(window, {pos + width, base, width, height});}
            void moveLeft()             { pos = std::max(0, pos - speed);}
            void moveRight()            { pos = std::min(windowWidth - width, pos + speed);}
    };

    Paddle              paddle;
    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , paddle(rect.w / 2, rect.h)
        {}

        virtual void doDraw() override
        {
            paddle.draw(*this);
        }
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& event) override
        {
            // SDL_KeyboardEvent:
            //  Uint8       repeat
            //  SDL_Keysym  keysym
            switch (event.keysym.sym)
            {
                case SDLK_q:    paddle.moveLeft();  break;
                case SDLK_w:    paddle.moveRight(); break;
                default:
                    break;
            }
        }

};


int main()
{
    UI::Application     application(UI::Video);
    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop([]()
    {
        SDL_Delay(16);
    });
}
