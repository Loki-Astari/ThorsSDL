#ifndef THORSANVIL_UI_EXAMPLE_PONG_GAME_LAYER
#define THORSANVIL_UI_EXAMPLE_PONG_GAME_LAYER

#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>

namespace ThorsAnvil::UI::Example::Pong
{

namespace UI = ThorsAnvil::UI;

class GameLayer
{
    class Paddle: public UI::Sprite
    {
        int const   speed           = 10;
        int const   height          = 18;
        int const   width           = 60;
        int const   border          = 4;
        //UI::Application& application;
        UI::Pen     pen{UI::C::black, UI::C::red};
        UI::Rect    position;
        int         windowWidth;
        public:
            Paddle(UI::Application& application, UI::Window& window, std::size_t layer, int windowWidth, int windowHeight);
            void moveLeft();
            void moveRight();
            bool collision(UI::Pt& ball, UI::Pt& velocity) const;
            virtual void doDraw(DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };

    class Score: public UI::Sprite
    {
        int             score;
        UI::TextPen     pen;
        UI::Texture     scoreText;
        public:
            Score(Window& parent, std::size_t layer);
            virtual void doDraw(DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
            void addPoints(int value);
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
            bool        state;
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
        Score&      score;
        public:
            Wall(Window& window, std::size_t layer, int windowWidth, int /*windowHeight*/, Score& score);
            virtual bool doUpdateState() override;
            virtual void doDraw(DrawContext& window) override;
            virtual void reset() override;
            bool collision(UI::Pt& ball, UI::Pt& velocity);
            bool doCollisionCheck(UI::Pt& ball, UI::Pt& velocity);
    };

    class Ball: public UI::Sprite
    {
        int const       radius          = 5;
        int const       windowWidth;
        int const       windowHeight;
        Window&         window;
        Paddle const&   paddle;
        Wall&           wall;
        UI::Pen         pen{UI::C::white, UI::C::white};
        UI::Pt          pos;
        UI::Pt          velocity;
        public:
            Ball(Window& parent, std::size_t layer, int windowWidth, int windowHeight, Paddle& paddle, Wall& wall);
            virtual void doDraw(DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };
    Paddle              paddle;
    Score               score;
    Wall                wall;
    Ball                ball;

    public:
        GameLayer(UI::Application& application, UI::Window& window, std::size_t layer, UI::Rect const& rect);
};

}

#endif
