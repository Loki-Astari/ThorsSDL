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

auto const IMG_ALL = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF;
Lib_Image::Lib_Image()
    : BaseWrapper(IMG_Init(IMG_ALL) == IMG_ALL ? 0 : -1, "Failed to Initialize SDL2 Image")
{}

Lib_Image::~Lib_Image()
{
    IMG_Quit();
}

Window::Window(std::string const& title, Rect const& rect, WindowState const& winState)
    : PointerWrapper(SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, winState), "Failed to Create SDL-Window")
{}

Window::~Window()
{
    if (pointer != nullptr) {
        SDL_DestroyWindow(pointer);
    }
}

Renderer::Renderer(SDL_Window* sdlWindow, RenderState const& renState)
    : PointerWrapper(SDL_CreateRenderer(sdlWindow, -1, renState), "Failed to Create SDL-Renderer")
{}

Renderer::~Renderer()
{
    if (pointer != nullptr) {
        SDL_DestroyRenderer(pointer);
    }
}

Surface::Surface()
    : PointerWrapper()
{}

Surface::Surface(SDL_Surface* surface, char const* message)
    : PointerWrapper(surface, message)
{}

Surface::~Surface()
{
    SDL_FreeSurface(pointer);
}

TTFont::TTFont(std::string const& fileName, int point)
    : PointerWrapper(TTF_OpenFont(fileName.c_str(), point), "Failed to Create TTF-Font. Did you init Lib_TTF (via the Application object)")
{}

TTFont::~TTFont()
{
    TTF_CloseFont(pointer);
}
