#ifndef THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_LAYER
#define THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_LAYER

#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>

namespace ThorsAnvil::UI::Example::Pong
{

namespace UI = ThorsAnvil::UI;

class HighScoreLayer
{
    struct HighScore
    {
        std::string     name;
        std::string     date;
        int             score;

        static std::string ltrim(const std::string &s)
        {
            size_t start = s.find_first_not_of(" \t");
            return (start == std::string::npos) ? "" : s.substr(start);
        }

        static std::string rtrim(const std::string &s)
        {
            size_t end = s.find_last_not_of(" \t");
            return (end == std::string::npos) ? "" : s.substr(0, end + 1);
        }

        static std::string trim(const std::string &s)
        {
            return rtrim(ltrim(s));
        }

        friend std::istream& operator>>(std::istream& stream, HighScore& data)
        {
            std::string tmp;

            std::getline(stream, tmp, ',');
            data.name = data.trim(tmp);

            std::getline(stream, tmp, ',');
            data.date = data.trim(tmp);

            stream >> data.score;
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return stream;
        }
        friend std::ostream& operator<<(std::ostream& stream, HighScore const& data)
        {
            return stream << data.name << ", " << data.date << ", " << data.score << "\n";
        }
    };
    class HighScoreTable: public UI::Sprite
    {
        Window&                     window;
        UI::TextPen                 pen;
        int&                        scoreOfLastGame;
        UI::Rect                    rect;
        std::vector<HighScore>      scores;

        public:
            HighScoreTable(Window& parent, std::size_t layer, int& scoreOfLastGame, UI::Rect const& rect);
            virtual void doDraw(DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };

    HighScoreTable       highScoreTable;

    public:
        HighScoreLayer(UI::Window& window, std::size_t layer, int& scoreOfLastGame, UI::Rect const& rect)
            : highScoreTable(window, layer, scoreOfLastGame, rect)
        {}
};

}

#endif
