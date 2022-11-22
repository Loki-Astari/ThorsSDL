#include "Application.h"
#include <stdexcept>


using namespace ThorsAnvil::UI;

bool Application::initialized = false;

Application::Application(InitValue init)
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

Application::~Application()
{
    SDL_Quit();
}

void Application::initSubSystem(InitValue init)
{
    auto result = SDL_InitSubSystem(static_cast<Uint32>(init));
    if (result != 0)
    {
        throw std::runtime_error("Failed to init sub system");
    }
}

void Application::quitSubSystem(InitValue init)
{
    SDL_QuitSubSystem(static_cast<Uint32>(init));
}
