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

Window::Window(std::string const& title, Rect const& rect, WindowState const& winState)
    : PointerWrapper(SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, winState), "Failed to Create SDL-Window")
{}

Window::~Window()
{
    SDL_DestroyWindow(pointer);
}

Renderer::Renderer(SDL_Window* sdlWindow, RenderState const& renState)
    : PointerWrapper(SDL_CreateRenderer(sdlWindow, -1, renState), "Failed to Create SDL-Renderer")
{}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(pointer);
}

Surface::Surface(SDL::TTFont& font, std::string const& message, Color const& ink)
    : PointerWrapper(TTF_RenderText_Solid(font, message.c_str(), SDL_Color{ink.r, ink.b, ink.g, ink.alpha}), "Failed to Create SDL-Surface")
{}

Surface::~Surface()
{
    SDL_FreeSurface(pointer);
}

TTFont::TTFont(std::string const& fileName, int point)
    : PointerWrapper(TTF_OpenFont(fileName.c_str(), point), "Failed to Create TTF-Font")
{}

TTFont::~TTFont()
{
    TTF_CloseFont(pointer);
}
