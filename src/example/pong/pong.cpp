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
            Paddle(int windowWidth, int windowHeight)
                : pos((windowWidth / 2) - (width / 2))
                , base(windowHeight - height - border)
            {}
            void draw(Window& window)   { pen.drawRect(window, {pos, base, width, height});}
            void moveLeft()             { pos = std::max(0, pos - speed);}
            void moveRight()            { pos = std::min(windowWidth - width, pos + speed);}
    };
    class Ball
    {
        int const   radius          = 5;
        UI::Pen     pen{UI::C::white, UI::C::white};
        UI::Pt      pos;
        UI::Pt      velocity;
        public:
            Ball(int windowWidth, int windowHeight)
                : pos{windowWidth / 2, windowHeight / 2}
                , velocity{-10, -10}
            {}
            void draw(Window& window)   { pen.drawRect(window, {pos.x - radius, pos.y - radius, 2*radius, 2*radius});}
            void move()                 { pos.x += velocity.x; pos.y += velocity.y;}
    };

    Paddle              paddle;
    Ball                ball;
    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , paddle(rect.w, rect.h)
            , ball(rect.w, rect.h)
        {}

        // Called on each window after all events have been handled.
        virtual void doDraw() override
        {
            paddle.draw(*this);
            ball.draw(*this);
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
        void update(int /*eventCount*/)
        {
            ball.move();
        }
};


int main()
{
    UI::Application     application(UI::Video);
    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop([]()
    {
        // Runs at the end of the event loop
        SDL_Delay(16);
    },
    [&window](int eventCount)
    {
        // Runs as the last event handler.
        // Chance to update the state before drawing.
        window.update(eventCount);
    }
    );
}
