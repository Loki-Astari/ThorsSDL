#include "ThorsSDL.h"


using namespace ThorsAnvil::UI::SDL;

BaseWrapper::~BaseWrapper()
{}

Lib_Main::Lib_Main(InitValue init)
    : BaseWrapper(SDL_Init(init), "Failed to Initialize SDL2")
{}

Lib_Main::~Lib_Main()
{
    SDL_Quit();
}

Lib_TTF::Lib_TTF()
    : BaseWrapper(TTF_Init(), "Failed to Initialize SDL2 TTF")
{}

Lib_TTF::~Lib_TTF()
{
    TTF_Quit();
}
