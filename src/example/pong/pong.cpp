#include "ThorsSDL/Application.h"
#include "GameLayer.h"
#include "HighScoreLayer.h"
#include <vector>

namespace UI = ThorsAnvil::UI;

int constexpr           windowWidth     = 1280;
int constexpr           windowHeight    = 720;

class PongWindow: public UI::Window
{
    ThorsAnvil::UI::Example::Pong::GameLayer           game;
    ThorsAnvil::UI::Example::Pong::HighScoreLayer      highScore;

    static int constexpr highScoreLayer = 0;
    static int constexpr gameLayer = 1;

    public:
        PongWindow(UI::Application& application, std::string const& title, UI::Rect const& rect, UI::WindowState const& winState = {}, UI::RenderState const& renState = {})
            : Window(application, title, rect, winState, renState)
            , game(application, *this, gameLayer, rect)
            , highScore(application, *this, highScoreLayer, rect)
        {}
};


int main()
{
    UI::Application     application(UI::Video, UI::Fonts);
    PongWindow          window(application, "Pong v1.0", {UI::windowUndefinedPos, UI::windowUndefinedPos, windowWidth, windowHeight}, {.grabFocus = true});

    application.eventLoop(60);
}
