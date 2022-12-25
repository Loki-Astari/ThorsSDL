#include "HighScoreView.h"

#include "ThorsUI/Application.h"

using namespace ThorsAnvil::Example::Pong;

HighScoreView::HighScoreTable::HighScoreTable(WI::View& parent, int& scoreOfLastGame)
    : layout(3, WI::FixedHeight, WI::Left, WI::Top)
    , view(parent, layout)
    , scoreOfLastGame(scoreOfLastGame)
{
    std::ifstream   highScore("HighScore.data");
    std::copy(std::istream_iterator<HighScore>(highScore), std::istream_iterator<HighScore>(), std::back_inserter(scores));

    labels.reserve(scores.size() * 3);
    buildLabels();
}

HighScoreView::HighScoreTable::~HighScoreTable()
{
    cleanLabels();
}

void HighScoreView::HighScoreTable::buildLabels()
{
    for (auto score: scores)
    {
        labels.emplace_back(new WI::WidgetLabel(view, std::move(score.name)));
        labels.emplace_back(new WI::WidgetLabel(view, std::move(score.date)));
        labels.emplace_back(new WI::WidgetLabel(view, std::to_string(score.score)));
    }
}

void HighScoreView::HighScoreTable::cleanLabels()
{
    for (WI::WidgetLabel* label: labels) {
        delete label;
    }
    labels.resize(0);
}

void HighScoreView::HighScoreTable::reset()
{
    auto find = std::find_if(std::begin(scores), std::end(scores), [scoreOfLastGame = this->scoreOfLastGame](HighScore const& item){return item.score < scoreOfLastGame;});
    if (find != std::end(scores))
    {
        nameDialog.show([&,find](std::string const& nameInput)
        {
            std::string name(nameInput);
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

            cleanLabels();
            buildLabels();
        });
    }
}

HighScoreView::ButtonPane::ButtonPane(WI::View& parent, std::function<void()>&& action)
    : layout(WI::Middle)
    , view(parent, layout)
    , quit(view, "Quit", [](){UI::Application::getInstance().exitLoop();})
    , play(view, "Play", std::move(action))
{}

HighScoreView::HighScoreRealView::HighScoreRealView(UI::Window& window, Widgets::Layout& layout, Widgets::Theme& theme, std::function<void()>&& action)
    : View(window, layout, theme)
    , action(std::move(action))
{}

UI::Sz HighScoreView::HighScoreRealView::reset(bool fitToWindow)
{
    action();
    return WI::View::reset(fitToWindow);
}

HighScoreView::HighScoreView::HighScoreView(UI::Window& window, int& scoreOfLastGame, std::function<void()>&& startGame)
    : layout{WI::Center}
    , theme{}
    , view(window, layout, theme, [&table = this->table](){table.reset();})
    , table(view, scoreOfLastGame)
    , buttons(view, std::move(startGame))
{
    theme.labelNormalTextPen = UI::TextPen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::powderblue);
    theme.butNormalTextPen   = UI::TextPen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::yellow);
    theme.butHoverTextPen    = UI::TextPen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::red);
    theme.butPressTextPen    = UI::TextPen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::white);
}
