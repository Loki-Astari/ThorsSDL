#include "HighScoreLayer.h"

#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace ThorsAnvil::UI::Example::Pong;

HighScoreLayer::HighScoreTable::HighScoreTable(UI::Window& parent, std::size_t layer, int& scoreOfLastGame, UI::Rect const& rect)
    : Sprite(parent, layer, 10)
    , window(parent)
    , pen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::powderblue)
    , scoreOfLastGame(scoreOfLastGame)
    , rect(rect)
{
    std::ifstream   highScore("HighScore.data");

    std::copy(std::istream_iterator<HighScore>(highScore), std::istream_iterator<HighScore>(), std::back_inserter(scores));
}

void HighScoreLayer::HighScoreTable::doDraw(UI::DrawContext& context)
{
    UI::Texture title   = pen.createTextureFromString(context, "High Score Table");
    title.doDraw({rect.w / 2 - 100, 100, 0, 0});

    int dist = 200;
    for (auto const& score: scores)
    {
        UI::Texture name    = pen.createTextureFromString(context, score.name);
        UI::Texture date    = pen.createTextureFromString(context, score.date);
        UI::Texture valu    = pen.createTextureFromString(context, std::to_string(score.score));

        name.doDraw({rect.w / 2 - 300, dist, 0, 0});
        date.doDraw({rect.w / 2 - 100, dist, 0, 0});
        valu.doDraw({rect.w / 2 + 200, dist, 0, 0});
        dist += 50;
    }

    UI::Texture instruct = pen.createTextureFromString(context, "Press: L to Play, K to Quit.   Game:  Q: Moves paddle left, W: Moves paddle right");
    instruct.doDraw({100, 600, 0, 0});
}

bool HighScoreLayer::HighScoreTable::doUpdateState()
{
    int numkeys = 0;
    Uint8 const* keystates = SDL_GetKeyboardState(&numkeys);
    if (keystates[SDL_SCANCODE_L])
    {
        window.updateLayer(1);
    }
    if (keystates[SDL_SCANCODE_K])
    {
        Application::getInstance().exitLoop();
    }
    return true;
}

void HighScoreLayer::HighScoreTable::reset()
{
    auto find = std::find_if(std::begin(scores), std::end(scores), [scoreOfLastGame = this->scoreOfLastGame](HighScore const& item){return item.score < scoreOfLastGame;});
    if (find != std::end(scores))
    {
        std::cout << "Please Enter Your Name: ";
        std::string name;
        std::getline(std::cin, name);
        name.erase(std::remove(std::begin(name),end(name), ','), std::end(name));

        const auto now = std::chrono::system_clock::now();
        //std::string date = std::format("{:%d/%m/%Y}", now);
        char date[16] = {0};
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::strftime(date, sizeof(date), "%Y/%m/%d", std::localtime(&time));

        scores.insert(find, {name, date, scoreOfLastGame});
        scores.resize(std::min(scores.size(), static_cast<std::size_t>(5)));

        std::ofstream   highScore("HighScore.data");

        std::copy(std::begin(scores), std::end(scores), std::ostream_iterator<HighScore>(highScore));
    }
}
