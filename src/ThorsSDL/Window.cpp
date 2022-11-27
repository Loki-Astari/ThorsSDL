#include "Window.h"
#include "Application.h"
#include "Sprite.h"

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
    : DrawContext(nullptr)
    , application(application)
    , window(nullptr)
    , sprites{}
{
    window  = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, winState);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create Window");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    try
    {
        static_cast<DrawContext&>(*this) = DrawContext(window, renState);
    }
    catch (...)
    {
        SDL_DestroyWindow(window);
        throw;
    }

    application.registerWindow(*this);
}

Window::~Window()
{
    destroy();
}

Window::Window(Window&& move) noexcept
    : DrawContext(std::move(move))
    , application(move.application)
    , window(nullptr)
{
    std::swap(window,   move.window);
    std::swap(sprites,  move.sprites);
    application.registerWindow(*this);
}

Window& Window::operator=(Window&& move) noexcept
{
    destroy();

    window = std::exchange(move.window, nullptr);
    sprites= std::exchange(move.sprites,{});
    static_cast<DrawContext&>(*this) = std::move(move);

    application.registerWindow(*this);
    return *this;
}

void Window::updateState()
{
    for (auto& sprite: sprites)
    {
        sprite->updateState();
    }
}

void Window::destroy()
{
    if (window != nullptr)
    {
        application.unregisterWindow(*this);
        SDL_DestroyWindow(window);
    }
}

Uint32 Window::getId() const
{
    return SDL_GetWindowID(window);
}

void Window::draw()
{
    Color const& background = getBackgroundColor();

    SDL_SetRenderDrawColor(getSurface(), background.r, background.g, background.b, background.alpha);
    SDL_RenderClear(getSurface());

    doDraw();

    for (auto const& sprite: sprites)
    {
        sprite->doDraw(*this);
    }

    SDL_RenderPresent(getSurface());
}

void Window::doDraw()
{
}

void Window::addSprite(Sprite& sprite)
{
    sprites.emplace_back(&sprite);
}

void Window::remSprite(Sprite& sprite)
{
    auto find = std::find(std::begin(sprites), std::end(sprites), &sprite);
    if (find != std::end(sprites))
    {
        sprites.erase(find);
    }
}
