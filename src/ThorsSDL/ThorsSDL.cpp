#include "ThorsSDL.h"
#include <stdexcept>


using namespace ThorsAnvil::UI;

bool ThorSDL::initialized = false;

ThorSDL::ThorSDL(InitValue init)
{
    if (initialized)
    {
        throw std::runtime_error("Attempt to re-initialize SDL");
    }
    auto result = SDL_Init(static_cast<Uint32>(init));
    if (result != 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }
    initialized = true;
}

ThorSDL::~ThorSDL()
{
    SDL_Quit();
}

void ThorSDL::initSubSystem(InitValue init)
{
    auto result = SDL_InitSubSystem(static_cast<Uint32>(init));
    if (result != 0)
    {
        throw std::runtime_error("Failed to init sub system");
    }
}

void ThorSDL::quitSubSystem(InitValue init)
{
    SDL_QuitSubSystem(static_cast<Uint32>(init));
}
