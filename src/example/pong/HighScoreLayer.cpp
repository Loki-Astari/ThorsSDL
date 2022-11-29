#include "HighScoreLayer.h"

#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>

using namespace ThorsAnvil::UI::Example::Pong;

HighScoreLayer::HighScoreTable::HighScoreTable(UI::Application& /*application*/, UI::Window& parent, std::size_t layer)
    : Sprite(parent, layer, 10)
    //, application(application)
    , window(parent)
    , pen("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24, UI::C::powderblue)
{}

void HighScoreLayer::HighScoreTable::doDraw(UI::DrawContext& /*context*/)
{
}

bool HighScoreLayer::HighScoreTable::doUpdateState()
{
    int numkeys = 0;
    Uint8 const* keystates = SDL_GetKeyboardState(&numkeys);
    if (keystates[SDL_SCANCODE_L])
    {
        window.updateLayer(1);
    }
    return true;
}
