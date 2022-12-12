#ifndef THORSANVIL_UI_EXAMPLE_PONG_GAME_VIEW
#define THORSANVIL_UI_EXAMPLE_PONG_GAME_VIEW

#include "ThorsUI/Pen.h"
#include "ThorsGraphics/Sprite.h"
#include "ThorsGraphics/View.h"
#include <vector>

namespace ThorsAnvil::UI
{
    class Window;
}

namespace ThorsAnvil::Example::Pong
{

namespace UI = ThorsAnvil::UI;
namespace GR = ThorsAnvil::Graphics;

class GameView: public GR::View
{
    class Paddle: public GR::Sprite
    {
        int const   speed           = 10;
        int const   height          = 18;
        int const   width           = 60;
        int const   border          = 4;
        UI::Pen     pen{UI::C::black, UI::C::red};
        UI::Rect    position;
        int         windowWidth;
        public:
            Paddle(GR::View& view, int windowWidth, int windowHeight);
            void moveLeft();
            void moveRight();
            bool collision(UI::Pt& ball, UI::Pt& velocity) const;
            virtual void draw(UI::DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };

    class Score: public GR::Sprite
    {
        int&            score;
        UI::TextPen     pen;
        //UI::Texture     scoreText;
        public:
            Score(GR::View& view, int& scoreOfLastGame);
            virtual void draw(UI::DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
            void addPoints(int value);
    };

    class Wall: public GR::Sprite
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
            Wall(GR::View& view, int windowWidth, int /*windowHeight*/, Score& score);
            virtual bool doUpdateState() override;
            virtual void draw(UI::DrawContext& window) override;
            virtual void reset() override;
            bool collision(UI::Pt& ball, UI::Pt& velocity);
            bool doCollisionCheck(UI::Pt& ball, UI::Pt& velocity);
    };

    class Ball: public GR::Sprite
    {
        int const       radius          = 5;
        int const       windowWidth;
        int const       windowHeight;
        Paddle const&   paddle;
        Wall&           wall;
        UI::Pen         pen{UI::C::white, UI::C::white};
        UI::Pt          pos;
        UI::Pt          velocity;
        std::function<void()>   endGame;
        public:
            Ball(GR::View& view, int windowWidth, int windowHeight, Paddle& paddle, Wall& wall, std::function<void()>&& endGame);
            virtual void draw(UI::DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };
    Paddle              paddle;
    Score               score;
    Wall                wall;
    Ball                ball;

    public:
        GameView(UI::Window& window, int& scoreOfLastGame, UI::Rect const& rect, std::function<void()>&& endGame);
};

}

#endif
