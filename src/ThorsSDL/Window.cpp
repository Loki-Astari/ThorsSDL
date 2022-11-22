#include "Window.h"
#include "Application.h"

using namespace ThorsAnvil::UI;

/*
    WindowType  type        = Default;
    bool        border      = true;
    bool        resizabel   = true;
    bool        hidden      = true;
    bool        focus       = true;
*/
/*
enum WindowFlags : Uint32
{
    FullScreen  = SDL_WINDOW_FULLSCREEN,        //: fullscreen window
    Desktop     = SDL_WINDOW_FULLSCREEN_DESKTOP //: fullscreen window at desktop resolution
    OpenGL      = SDL_WINDOW_OPENGL,            //: window usable with an OpenGL context
    Vulkan      = SDL_WINDOW_VULKAN,            //: window usable with a Vulkan instance
    Metal       = SDL_WINDOW_METAL,             //: window usable with a Metal instance
    Hidden      = SDL_WINDOW_HIDDEN,            //: window is not visible
    Borderless  = SDL_WINDOW_BORDERLESS,        //: no window decoration
    Resizable   = SDL_WINDOW_RESIZABLE,         //: window can be resized
    Minimized   = SDL_WINDOW_MINIMIZED,         //: window is minimized
    Maximized   = SDL_WINDOW_MAXIMIZED,         //: window is maximized
    Focus       = SDL_WINDOW_INPUT_GRABBED      //: window has grabbed input focus
    HighDPI     = SDL_WINDOW_ALLOW_HIGHDPI,     //: window should be created in high-DPI mode if supported (>= SDL 2.0.1)
};
*/

WindowState::operator Uint32() const
{
    Uint32  flags   = static_cast<Uint32>(type)
                    | (border ? 0 : SDL_WINDOW_BORDERLESS)
                    | (resizeable ? SDL_WINDOW_RESIZABLE : 0)
                    | (hidden ? SDL_WINDOW_HIDDEN : 0)
                    | (focus ? SDL_WINDOW_INPUT_GRABBED : 0);
    return flags;
}

Window::Window(Application& application, std::string const& title, Rect const& rect, WindowState state)
    : application(application)
    , window(nullptr)
    , renderer(nullptr)
{
    window  = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, state);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create Window");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
        SDL_DestroyWindow(window);
    }
    application.unregisterWindow(*this);
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
    static constexpr Color background{96, 128, 255, 255};

    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.alpha);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
