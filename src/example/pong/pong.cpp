#include "GameView.h"
#include "HighScoreView.h"
#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include <vector>

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    int                                             scoreOfLastGame;
    ThorsAnvil::Example::Pong::GameView             gameView;
    ThorsAnvil::Example::Pong::HighScoreView        highScoreView;

    static int constexpr highScoreViewId = 0;
    static int constexpr gameViewId = 1;

    public:
        PongWindow(std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(title, rect, winState, renState)
            , scoreOfLastGame(0)
            , gameView(scoreOfLastGame, rect, [window = this](){window->updateView(highScoreViewId);})
            , highScoreView(scoreOfLastGame, rect, [window = this](){window->updateView(gameViewId);})
        {
            addView(highScoreView);
            addView(gameView);
        }
};


int main()
{
    UI::Application    application(UI::Video, UI::Fonts);
    PongWindow          window("Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop(60);
}
