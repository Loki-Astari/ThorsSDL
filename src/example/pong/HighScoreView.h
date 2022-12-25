#ifndef THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_VIEW
#define THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_VIEW

#include "ThorsWidgets/Layout.h"
#include "ThorsWidgets/Theme.h"
#include "ThorsWidgets/View.h"
#include "ThorsWidgets/WidgetView.h"
#include "ThorsWidgets/WidgetLabel.h"
#include "ThorsWidgets/WidgetButton.h"
#include "ThorsWidgets/Dialog.h"

#include <fstream>
#include <string>

namespace ThorsAnvil::Example::Pong
{

namespace UI = ThorsAnvil::UI;
namespace WI = ThorsAnvil::Widgets;

class HighScoreView
{
    class NameDialog: public Widgets::Dialog<std::string>
    {
        public:
            NameDialog()
                : Dialog("Name: ")
            {}
    };
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

    class HighScoreTable
    {
        WI::GridLayout                  layout;
        WI::WidgetView                  view;
        std::vector<HighScore>          scores;
        std::vector<WI::WidgetLabel*>   labels;
        NameDialog                      nameDialog;
        int&                            scoreOfLastGame;
        public:
            HighScoreTable(WI::View& parent, int& scoreOfLastGame);
            ~HighScoreTable();

            void reset();
        private:
            void buildLabels();
            void cleanLabels();
    };

    class ButtonPane
    {
        WI::HorzBoxLayout   layout;
        WI::WidgetView      view;
        WI::WidgetButton    quit;
        WI::WidgetButton    play;
        public:
            ButtonPane(WI::View& parent, std::function<void()>&& action);
    };

    class HighScoreRealView: public WI::View
    {
        std::function<void()>   action;
        public:
            HighScoreRealView(UI::Window& window, Widgets::Layout& layout, Widgets::Theme& theme, std::function<void()>&& action);
            virtual UI::Sz reset(bool fitToWindow) override;
    };

    WI::VertBoxLayout   layout;
    WI::Theme           theme;
    HighScoreRealView   view;
    HighScoreTable      table;
    ButtonPane          buttons;
    public:
        HighScoreView(UI::Window& window, int& scoreOfLastGame, std::function<void()>&& startGame);
};

}

#endif
