#include "Application.h"
#include "Window.h"
#include <stdexcept>
#include <iostream>


using namespace ThorsAnvil::UI;

bool Application::initialized = false;

Application::Application(InitValue init)
    : finished(false)
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

void Application::eventLoop(std::function<void()>&& action)
{
    try
    {
        while (!finished)
        {
            handleEvents();
            drawWindows();
            action();
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void Application::exitLoop()
{
    finished    = true;
}

void Application::registerWindow(Window& window)
{
    windows[window.window] = &window;
}

void Application::unregisterWindow(Window& window)
{
    windows.erase(windows.find(window.window));
}

void Application::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:  exitLoop();break;
            default:
                break;
        }
    }
}

void Application::drawWindows()
{
    for (auto& window: windows)
    {
        window.second->draw();
    }
}
