#include "ThorsSDL/Application.h"
#include "GameLayer.h"
#include "HighScoreLayer.h"
#include <vector>

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    int                                             scoreOfLastGame;
    ThorsAnvil::UI::Example::Pong::GameLayer        gameLayer;
    ThorsAnvil::UI::Example::Pong::HighScoreLayer   highScoreLayer;

    static int constexpr highScoreLayerId = 0;
    static int constexpr gameLayerId = 1;

    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , scoreOfLastGame(0)
            , gameLayer(application, *this, gameLayerId, scoreOfLastGame, rect)
            , highScoreLayer(application, *this, highScoreLayerId, scoreOfLastGame, rect)
        {}
};


int main()
{
    UI::Application     application(UI::Video, UI::Fonts);
    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop(60);
}
