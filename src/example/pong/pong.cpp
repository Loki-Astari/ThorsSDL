#include "GameView.h"
#include "HighScoreView.h"
#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include <vector>

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    int                                             scoreOfLastGame;
    ThorsAnvil::Example::Pong::HighScoreView        highScoreView;
    ThorsAnvil::Example::Pong::GameView             gameView;

    static int constexpr highScoreViewId = 0;
    static int constexpr gameViewId = 1;

    public:
        PongWindow(std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(title, rect, winState, renState)
            , scoreOfLastGame(0)
            , highScoreView(*this, scoreOfLastGame, [window = this](){window->updateView(gameViewId);})
            , gameView(*this, scoreOfLastGame, rect, [window = this](){window->updateView(highScoreViewId);})
        {
        }
};


int main()
{
    UI::Application    application(UI::Video, UI::Fonts);
    PongWindow          window("Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop(60);
}
