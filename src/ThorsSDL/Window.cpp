#include "Window.h"
#include "Application.h"

using namespace ThorsAnvil::UI;

WindowState::operator Uint32() const
{
    Uint32  flags   = static_cast<Uint32>(type)
                    | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
                    | (border ? 0 : SDL_WINDOW_BORDERLESS)
                    | (resizeable ? SDL_WINDOW_RESIZABLE : 0)
                    | (hidden ? SDL_WINDOW_HIDDEN : 0)
                    | (grabFocus ? SDL_WINDOW_INPUT_GRABBED : 0);
    return flags;
}

RenderState::operator Uint32() const
{
    Uint32  flags   = (software ? SDL_RENDERER_SOFTWARE : 0)
                    | (accelerated ? SDL_RENDERER_ACCELERATED : 0)
                    | (presentSync ? SDL_RENDERER_PRESENTVSYNC : 0)
                    | (targetText ? SDL_RENDERER_TARGETTEXTURE : 0);
    return flags;
}

Window::Window(Application& application, std::string const& title, Rect const& rect, WindowState const& winState, RenderState const& renState)
    : application(application)
    , window(nullptr)
    , renderer(nullptr)
{
    window  = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, winState);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create Window");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, renState);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer");
    }

    application.registerWindow(*this);
}

Window::~Window()
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr)
    {
        application.unregisterWindow(*this);
        SDL_DestroyWindow(window);
    }
}

Window::Window(Window&& move) noexcept
    : application(move.application)
    , window(nullptr)
    , renderer(nullptr)
{
    std::swap(window,   move.window);
    std::swap(renderer, move.renderer);
    application.registerWindow(*this);
}

Window& Window::operator=(Window&& move) noexcept
{
    application.unregisterWindow(*this);

    std::swap(window,   move.window);
    std::swap(renderer, move.renderer);
    application.registerWindow(*this);
    return *this;
}

void Window::draw()
{
    Color const& background = getBackgroundColor();

    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.alpha);
    SDL_RenderClear(renderer);
    doDraw();
    SDL_RenderPresent(renderer);
}

void Window::doDraw()
{
}
