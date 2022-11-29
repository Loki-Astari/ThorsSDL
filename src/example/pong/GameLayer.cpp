#include "GameLayer.h"
#include "ThorsSDL/DrawContext.h"

using namespace ThorsAnvil::UI::Example::Pong;

GameLayer::Paddle::Paddle(UI::Application& application, UI::Window& window, std::size_t layer, int windowWidth, int windowHeight)
    : Sprite(window, layer, 15)
    , application(application)
    , position{ (windowWidth / 2) - (width / 2), windowHeight - height - border, width, height}
    , windowWidth(windowWidth)
{}

void GameLayer::Paddle::moveLeft()
{
    position.x = std::max(0, position.x - speed);
}

void  GameLayer::Paddle::moveRight()
{
    position.x = std::min(windowWidth - width, position.x + speed);
}

bool  GameLayer::Paddle::collision(UI::Pt& ball, UI::Pt& velocity) const
{
    bool hit = position.bounce(ball, velocity);
    return hit;
}

void  GameLayer::Paddle::doDraw(DrawContext& context)
{
    pen.drawRect(context, position);
}

bool  GameLayer::Paddle::doUpdateState()
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

GameLayer::Score::Score(Window& parent, std::size_t layer)
    : Sprite(parent, layer, 16)
    , score(0)
    , pen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24)
    , scoreText(pen.createTextureFromString(parent, "Current Score: "))
{}

void GameLayer::Score::doDraw(DrawContext& context)
{
    scoreText.doDraw();

    UI::Texture     scoreValue = pen.createTextureFromString(context, std::to_string(score).c_str());
    scoreValue.doDraw({250, 0, 0, 0});
}

bool GameLayer::Score::doUpdateState()
{
    return false;
}

void GameLayer::Score::addPoints(int value)
{
    score += value;
}

GameLayer::Wall::Wall(Window& window, std::size_t layer, int windowWidth, int /*windowHeight*/, Score& score)
    : Sprite(window, layer, 10000)
    , brickWidth((windowWidth / bricksPerRow) - cementSpace)
    , offset((windowWidth - ((brickWidth + cementSpace) * bricksPerRow)) / 2)
    , score(score)
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

bool GameLayer::Wall::doUpdateState()
{
    return true;
}

void GameLayer::Wall::doDraw(DrawContext& window)
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

bool GameLayer::Wall::collision(UI::Pt& ball, UI::Pt& velocity)
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

bool GameLayer::Wall::doCollisionCheck(UI::Pt& ball, UI::Pt& velocity)
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

GameLayer::Ball::Ball(Window& parent, std::size_t layer, int windowWidth, int windowHeight, Paddle& paddle, Wall& wall)
    : Sprite(parent, layer, 15)
    , windowWidth(windowWidth)
    , windowHeight(windowHeight)
    , window(parent)
    , paddle(paddle)
    , wall(wall)
    , pos{windowWidth / 2, windowHeight / 2}
    , velocity{-4, -4}
{}

void GameLayer::Ball::doDraw(DrawContext& context)
{
    pen.drawRect(context, {pos.x - radius, pos.y - radius, 2*radius, 2*radius});
}

bool GameLayer::Ball::doUpdateState()
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
        window.updateLayer(0);
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
