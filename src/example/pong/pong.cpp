#include "ThorsSDL/ThorsSDL.h"
#include "ThorsSDL/DebugApplication.h"

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    class Paddle
    {
        int const   speed           = 40;
        int const   height          = 18;
        int const   width           = 60;
        int const   border          = 4;
        UI::Pen     pen{UI::C::black, UI::C::red};
        UI::Rect    position;
        public:
            Paddle(int windowWidth, int windowHeight)
                : position{ (windowWidth / 2) - (width / 2), windowHeight - height - border, width, height}
            {}
            void draw(Window& window)   { pen.drawRect(window, position);}
            void moveLeft()             { position.x = std::max(0, position.x - speed);}
            void moveRight()            { position.x = std::min(windowWidth - width, position.x + speed);}
            bool collision(UI::Pt& ball, UI::Pt& velocity) const
            {
                if (position.contains(ball))
                {
                    velocity.y  = -velocity.y;
                    ball.y = 2 * position.y - ball.y;
                    return true;
                }
                return false;
            }
    };
    class Wall
    {
        int const   border          = 80;
        int const   cementSpace     = 3;
        int const   brickHeight     = 20;
        int const   bricksPerRow    = 20;
        int const   rowCount        = 10;
        UI::Pen     pens[8]         = {{UI::C::black, UI::C::yellow}, {UI::C::black, UI::C::yellow}, {UI::C::black, UI::C::green}, {UI::C::black, UI::C::green},
                                       {UI::C::black, UI::C::grey}, {UI::C::black, UI::C::grey}, {UI::C::black, UI::C::antiquewhite}, {UI::C::black, UI::C::antiquewhite}
                                      };
        int const   brickWidth;
        public:
            Wall(int windowWidth, int /*windowHeight*/)
                : brickWidth(windowWidth / bricksPerRow)
            {}
            void draw(Window& window)
            {
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int col = 0; col < bricksPerRow; ++col)
                    {
                        pens[row % std::size(pens)].drawRect(window, {col * (brickWidth + cementSpace), border + row * (brickHeight + cementSpace), brickWidth, brickHeight});
                    }
                }
            }
            bool collision(UI::Pt& /*ball*/, UI::Pt& /*velocity*/) const
            {
                return false;
            }
    };

    class Ball
    {
        int const       radius          = 5;
        int const       windowWidth;
        int const       windowHeight;
        Paddle const&   paddle;
        Wall&           wall;
        UI::Pen         pen{UI::C::white, UI::C::white};
        UI::Pt          pos;
        UI::Pt          velocity;
        public:
            Ball(int windowWidth, int windowHeight, Paddle& paddle, Wall& wall)
                : windowWidth(windowWidth)
                , windowHeight(windowHeight)
                , paddle(paddle)
                , wall(wall)
                , pos{windowWidth / 2, windowHeight / 2}
                , velocity{-2, -2}
            {}
            void draw(Window& window)   { pen.drawRect(window, {pos.x - radius, pos.y - radius, 2*radius, 2*radius});}
            bool move()
            {
                pos.x += velocity.x;
                pos.y += velocity.y;
                if (paddle.collision(pos, velocity))
                {   // Do Nothing
                }
                else if (wall.collision(pos, velocity))
                {   // Do Nothing
                }
                else if (pos.y < 0)
                {
                    pos.y       = (pos.y < 0 ? 0 : 2 * windowHeight) - pos.y;
                    velocity.y  = -velocity.y;
                }
                else if (pos.y > windowHeight)
                {
                    return false;
                }
                if ((pos.x < 0) || (pos.x > windowWidth))
                {
                    pos.x       = (pos.x < 0 ? 0 : 2 * windowWidth) - pos.x;
                    velocity.x  = -velocity.x;
                }

                return true;
            }
    };
    UI::Application&    application;
    Paddle              paddle;
    Wall                wall;
    Ball                ball;

    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , application(application)
            , paddle(rect.w, rect.h)
            , wall(rect.w, rect.h)
            , ball(rect.w, rect.h, paddle, wall)
        {}

        // Called on each window after all events have been handled.
        virtual void doDraw() override
        {
            paddle.draw(*this);
            wall.draw(*this);
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
            if (!ball.move())
            {
                application.exitLoop();
            }
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
