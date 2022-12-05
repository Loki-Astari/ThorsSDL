#include "GameView.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::Example::Pong;

GameView::Paddle::Paddle(GR::GraphicView& view, int windowWidth, int windowHeight)
    : Sprite(view, 15)
    , position{ (windowWidth / 2) - (width / 2), windowHeight - height - border, width, height}
    , windowWidth(windowWidth)
{}

void GameView::Paddle::moveLeft()
{
    position.x = std::max(0, position.x - speed);
}

void GameView::Paddle::moveRight()
{
    position.x = std::min(windowWidth - width, position.x + speed);
}

bool GameView::Paddle::collision(UI::Pt& ball, UI::Pt& velocity) const
{
    bool hit = position.bounce(ball, velocity);
    return hit;
}

void GameView::Paddle::draw(ThorsAnvil::UI::DrawContext& context)
{
    pen.drawRect(context, position);
}

bool GameView::Paddle::doUpdateState()
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
    return updated;
}

void GameView::Paddle::reset()
{
    position.x = (windowWidth/ 2) - (width / 2);
}

GameView::Score::Score(GR::GraphicView& view, int& scoreOfLastGame)
    : Sprite(view, 16)
    , score(scoreOfLastGame)
    , pen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24)
{}

void GameView::Score::draw(ThorsAnvil::UI::DrawContext& context)
{
    UI::Texture     scoreText(pen.createTextureFromString(context, "Current Score: "));
    scoreText.draw();

    UI::Texture     scoreValue = pen.createTextureFromString(context, std::to_string(score).c_str());
    scoreValue.draw({250, 0, 0, 0});
}

bool GameView::Score::doUpdateState()
{
    return false;
}

void GameView::Score::reset()
{
    score = 0;
}

void GameView::Score::addPoints(int value)
{
    score += value;
}

GameView::Wall::Wall(GR::GraphicView& view, int windowWidth, int /*windowHeight*/, Score& score)
    : Sprite(view, 10000)
    , brickWidth((windowWidth / bricksPerRow) - cementSpace)
    , offset((windowWidth - ((brickWidth + cementSpace) * bricksPerRow)) / 2)
    , score(score)
{
    reset();
}

bool GameView::Wall::doUpdateState()
{
    return true;
}

void GameView::Wall::draw(ThorsAnvil::UI::DrawContext& window)
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

void GameView::Wall::reset()
{
    bricks.clear();
    for (int row = 0; row < rowCount; ++row)
    {
        bricks.emplace_back();
        for (int col = 0; col < bricksPerRow; ++col)
        {
            bricks[row].emplace_back(offset + col * (brickWidth + cementSpace), border + row * (brickHeight + cementSpace), brickWidth, brickHeight, cementSpace);
        }
    }
}

bool GameView::Wall::collision(UI::Pt& ball, UI::Pt& velocity)
{
    bool hit = false;
    while (doCollisionCheck(ball, velocity))
    {
        hit = true;
        score.addPoints(10);
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

bool GameView::Wall::doCollisionCheck(UI::Pt& ball, UI::Pt& velocity)
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

GameView::Ball::Ball(GR::GraphicView& view, int windowWidth, int windowHeight, Paddle& paddle, Wall& wall, std::function<void()>&& endGame)
    : Sprite(view, 15)
    , windowWidth(windowWidth)
    , windowHeight(windowHeight)
    //, window(parent)
    , paddle(paddle)
    , wall(wall)
    , pos{windowWidth / 2, windowHeight / 2}
    , velocity{-4, -4}
    , endGame(std::move(endGame))
{}

void GameView::Ball::draw(ThorsAnvil::UI::DrawContext& context)
{
    pen.drawRect(context, {pos.x - radius, pos.y - radius, 2*radius, 2*radius});
}

bool GameView::Ball::doUpdateState()
{
    if (!paddle.collision(pos, velocity) && !wall.collision(pos, velocity))
    {
        // Did not hit paddle or wall so advance.
        // Note:    if the ball hit the paddle or wall then its position has already
        //          been updated.
        pos.x += velocity.x;
        pos.y += velocity.y;
    }
    if (pos.y > windowHeight)
    {
        endGame();
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

void GameView::Ball::reset()
{
    pos         = {windowWidth / 2, windowHeight / 2};
    velocity    = {-4, -4};
}

GameView::GameView(int& scoreOfLastGame, UI::Rect const& rect, std::function<void()>&& endGame)
    : paddle(*this, rect.w, rect.h)
    , score(*this, scoreOfLastGame)
    , wall(*this, rect.w, rect.h, score)
    , ball(*this, rect.w, rect.h, paddle, wall, std::move(endGame))
{}
