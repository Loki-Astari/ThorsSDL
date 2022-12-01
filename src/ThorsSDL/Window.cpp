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

WindowRegister::WindowRegister(Window& window)
    : window(window)
{
    window.registerWindow();
}

WindowRegister::~WindowRegister()
{
    window.unregisterWindow();
}

Window::Window(std::string const& title, Rect const& rect, WindowState const& winState, RenderState const& renState)
    : DrawContext(nullptr)
    , window(std::make_unique<SDL::Window>(title, rect, winState))
    , windowRegister(*this)
    , sprites{std::vector<Sprite*>{}}
    , currentSpriteLayer(0)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    static_cast<DrawContext&>(*this) = DrawContext(*window, renState);
}

Window::~Window()
{}

Window::Window(Window&& move) noexcept
    : DrawContext(std::move(move))
    , windowRegister(*this)
    , sprites{}
    , currentSpriteLayer(0)
{
    std::swap(window,               move.window);
    std::swap(sprites,              move.sprites);
    std::swap(currentSpriteLayer,   move.currentSpriteLayer);
    Application::getInstance().registerWindow(*this);
}

Window& Window::operator=(Window&& move) noexcept
{
    unregisterWindow();

    window              = std::exchange(move.window, nullptr);
    sprites             = std::exchange(move.sprites, {});
    currentSpriteLayer  = std::exchange(move.currentSpriteLayer, 0);
    static_cast<DrawContext&>(*this) = std::move(move);

    registerWindow();
    return *this;
}

void Window::registerWindow()
{
    if (window)
    {
        Application::getInstance().registerWindow(*this);
    }
}

void Window::unregisterWindow()
{
    if (window)
    {
        Application::getInstance().unregisterWindow(*this);
    }
}

void Window::updateLayer(std::size_t layer)
{
    sprites.resize(std::max(sprites.size(), layer+1));
    currentSpriteLayer = layer;
    for (auto& sprite: sprites[currentSpriteLayer])
    {
        sprite->reset();
    }
}

void Window::updateState()
{
    for (auto& sprite: sprites[currentSpriteLayer])
    {
        sprite->updateState();
    }
}

Uint32 Window::getId() const
{
    return SDL_GetWindowID(*window);
}

void Window::draw()
{
    Color const& background = getBackgroundColor();

    SDL_SetRenderDrawColor(getSurface(), background.r, background.g, background.b, background.alpha);
    SDL_RenderClear(getSurface());

    for (auto const& sprite: sprites[currentSpriteLayer])
    {
        sprite->doDraw(*this);
    }

    SDL_RenderPresent(getSurface());
}

void Window::addSprite(Sprite& sprite, std::size_t layer)
{
    sprites.resize(std::max(sprites.size(), layer + 1));
    sprites[layer].emplace_back(&sprite);
}

void Window::remSprite(Sprite& sprite)
{
    for (auto& spriteLayer: sprites)
    {
        auto find = std::find(std::begin(spriteLayer), std::end(spriteLayer), &sprite);
        if (find != std::end(spriteLayer))
        {
            spriteLayer.erase(find);
        }
    }
}
