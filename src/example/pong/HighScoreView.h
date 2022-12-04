#ifndef THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_VIEW
#define THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_VIEW

#include "ThorsGraphics/GraphicView.h"
#include "ThorsGraphics/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>

namespace ThorsAnvil::Example::Pong
{

namespace UI = ThorsAnvil::UI;
namespace GR = ThorsAnvil::Graphics;

class HighScoreView: public GR::GraphicView
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
    class HighScoreTable: public Graphics::Sprite
    {
        //Window&                     window;
        UI::TextPen                 pen;
        int&                        scoreOfLastGame;
        UI::Rect                    rect;
        std::vector<HighScore>      scores;
        std::function<void()>       startGame;

        public:
            HighScoreTable(GR::GraphicView& view, int& scoreOfLastGame, UI::Rect const& rect, std::function<void()>&& startGame);
            virtual void doDraw(UI::DrawContext& context) override;
            virtual bool doUpdateState() override;
            virtual void reset() override;
    };

    HighScoreTable       highScoreTable;

    public:
        HighScoreView(int& scoreOfLastGame, UI::Rect const& rect, std::function<void()>&& startGame);
};

}

#endif
