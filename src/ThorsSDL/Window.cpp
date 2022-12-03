#include "Window.h"
#include "Application.h"
#include "View.h"

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
    , views{}
    , currentView(0)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    static_cast<DrawContext&>(*this) = DrawContext(*window, renState);
}

Window::~Window()
{}

Window::Window(Window&& move) noexcept
    : DrawContext(std::move(move))
    , windowRegister(*this)
    , views{}
    , currentView(0)
{
    std::swap(window,       move.window);
    std::swap(views,        move.views);
    std::swap(currentView,  move.currentView);
    Application::getInstance().registerWindow(*this);
}

Window& Window::operator=(Window&& move) noexcept
{
    unregisterWindow();

    window      = std::exchange(move.window, nullptr);
    views       = std::exchange(move.views, {});
    currentView = std::exchange(move.currentView, 0);
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

void Window::updateView(std::size_t nextView)
{
    currentView = nextView;
    if (currentView < views.size())
    {
        views[currentView]->reset();
    }
}

void Window::updateState()
{
    if (currentView < views.size())
    {
        views[currentView]->updateState();
    }
}

Uint32 Window::getId() const
{
    return SDL_GetWindowID(*window);
}

void Window::draw()
{
    Color const& background = getBackgroundColor();

    SDL_SetRenderDrawColor(getRenderer(), background.r, background.g, background.b, background.alpha);
    SDL_RenderClear(getRenderer());

    if (currentView < views.size())
    {
        views[currentView]->doDraw(*this);
    }

    SDL_RenderPresent(getRenderer());
}

void Window::addView(View& view)
{
    views.emplace_back(&view);
}

void Window::remView(View& view)
{
    auto find = std::find(std::begin(views), std::end(views), &view);
    if (find != std::end(views))
    {
        views.erase(find);
    }
}
