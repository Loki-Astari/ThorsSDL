#include "ThorsSDL/ThorsSDL.h"
#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include <vector>

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    class Paddle: public UI::Sprite
    {
        int const   speed           = 10;
        int const   height          = 18;
        int const   width           = 60;
        int const   border          = 4;
        UI::Application& application;
        UI::Pen     pen{UI::C::black, UI::C::red};
        UI::Rect    position;
        public:
            Paddle(UI::Application& application, UI::Window& window, int windowWidth, int windowHeight)
                : Sprite(window, 15)
                , application(application)
                , position{ (windowWidth / 2) - (width / 2), windowHeight - height - border, width, height}
            {}
            void moveLeft()             { position.x = std::max(0, position.x - speed);}
            void moveRight()            { position.x = std::min(windowWidth - width, position.x + speed);}
            bool collision(UI::Pt& ball, UI::Pt& velocity) const
            {
                bool hit = position.bounce(ball, velocity);
                return hit;
            }
            virtual void doDraw(DrawContext& context) override
            {
                pen.drawRect(context, position);
            }
            virtual bool doUpdateState() override
            {
                bool updated = false;
                int numkeys = 0;
                Uint8 const* keystates = SDL_GetKeyboardState(&numkeys);
                if (keystates[SDL_SCANCODE_Q])
                {
                    moveLeft();
                    updated = true;
                }
                if (keystates[SDL_SCANCODE_W])
                {
                    moveRight();
                    updated = true;
                }
                if (keystates[SDL_SCANCODE_P])
                {
                    application.exitLoop();
                }
                return updated;
            }
    };
    class Wall: public UI::Sprite
    {
        struct Brick
        {
            Brick(int x, int y, int w, int h, int cementSpace)
                : drawRect{x, y, w, h}
                , collisionRect{x, y, w + cementSpace, h + cementSpace}
                , state(true)
            {}
            UI::Rect    drawRect;
            UI::Rect    collisionRect;
            bool                    state;
        };
        int const   border          = 80;
        int const   cementSpace     = 3;
        int const   brickHeight     = 20;
        int const   bricksPerRow    = 20;
        int const   rowCount        = 10;
        std::vector<std::vector<Brick>>  bricks;
        UI::Pen     pens[8]         = {{UI::C::black, UI::C::yellow}, {UI::C::black, UI::C::yellow}, {UI::C::black, UI::C::green}, {UI::C::black, UI::C::green},
                                       {UI::C::black, UI::C::grey}, {UI::C::black, UI::C::grey}, {UI::C::black, UI::C::antiquewhite}, {UI::C::black, UI::C::antiquewhite}
                                      };
        int const   brickWidth;
        int const   offset;             // offset from left of screen.
        public:
            Wall(Window& window, int windowWidth, int /*windowHeight*/)
                : Sprite(window, 10000)
                , brickWidth((windowWidth / bricksPerRow) - cementSpace)
                , offset((windowWidth - ((brickWidth + cementSpace) * bricksPerRow)) / 2)
            {
                for (int row = 0; row < rowCount; ++row)
                {
                    bricks.emplace_back();
                    for (int col = 0; col < bricksPerRow; ++col)
                    {
                        bricks[row].emplace_back(offset + col * (brickWidth + cementSpace), border + row * (brickHeight + cementSpace), brickWidth, brickHeight, cementSpace);
                    }
                }
            }
            virtual bool doUpdateState() override {return true;}
            virtual void doDraw(DrawContext& window) override
            {
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int col = 0; col < bricksPerRow; ++col)
                    {
                        if (bricks[row][col].state)
                        {
                            pens[row % std::size(pens)].drawRect(window, bricks[row][col].drawRect);
                        }
                    }
                }
            }
            bool collision(UI::Pt& ball, UI::Pt& velocity)
            {
                bool hit = false;
                while (doCollisionCheck(ball, velocity))
                {
                    hit = true;
                    ball.y -= velocity.y;
                    ball.x -= velocity.x;
                }
                if (hit)
                {
                    ball.y += velocity.y;
                    ball.x += velocity.x;
                }
                return hit;
            }
            bool doCollisionCheck(UI::Pt& ball, UI::Pt& velocity)
            {
                int col = ball.x / (brickWidth + cementSpace);
                int row = (ball.y - border) / (brickHeight + cementSpace);

                for (int r = -1; r < 2; ++r)
                {
                    int testRow = row + r;
                    for (int c = -1; c < 2; ++c)
                    {
                        int testCol = col + c;
                        if (   (testRow < 0 || testRow >= rowCount)
                            || (testCol < 0 || testCol >= bricksPerRow)
                            || (testCol == 0 && testRow == 0)
                            || (!bricks[testRow][testCol].state)
                           )
                        {
                            continue;
                        }
                        if (bricks[testRow][testCol].collisionRect.bounce(ball, velocity))
                        {
                            bricks[testRow][testCol].state = false;
                            return true;
                        }
                    }
                }

                return false;
            }
    };

    class Ball: public UI::Sprite
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
            Ball(Window& parent, int windowWidth, int windowHeight, Paddle& paddle, Wall& wall)
                : Sprite(parent, 15)
                , windowWidth(windowWidth)
                , windowHeight(windowHeight)
                , paddle(paddle)
                , wall(wall)
                , pos{windowWidth / 2, windowHeight / 2}
                , velocity{-4, -4}
            {}
            virtual void doDraw(DrawContext& context) override
            {
                pen.drawRect(context, {pos.x - radius, pos.y - radius, 2*radius, 2*radius});
            }
            virtual bool doUpdateState() override
            {
                if (!paddle.collision(pos, velocity) && !wall.collision(pos, velocity))
                {
                    // Did not hit paddle or wall so advance.
                    // Note:    if the ball hit the paddle or wall then its position has already
                    //          been updated.
                    pos.x += velocity.x;
                    pos.y += velocity.y;
                }

                // Check with collision with walls.
                if (pos.y < 0)
                {
                    pos.y       = (pos.y < 0 ? 0 : 2 * windowHeight) - pos.y;
                    velocity.y  = -velocity.y;
                }
                if ((pos.x < 0) || (pos.x > windowWidth))
                {
                    pos.x       = (pos.x < 0 ? 0 : 2 * windowWidth) - pos.x;
                    velocity.x  = -velocity.x;
                }
                return true;
            }
    };
    Paddle              paddle;
    Wall                wall;
    Ball                ball;

    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , paddle(application, *this, rect.w, rect.h)
            , wall(*this, rect.w, rect.h)
            , ball(*this, rect.w, rect.h, paddle, wall)
        {}
};


int main()
{
    UI::Application     application(UI::Video, UI::Fonts);
    TTF_Font*   font = TTF_OpenFont("arial.ttf", "14");

    SDL_Color       color{255, 255, 255};
    SDL_Surface*    surface = TTF_RenderText_Solid(font, "Welcome to Gigi Labs", color);
    SDL_Texture*    texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop(60);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
