#include "ThorsSDL.h"
#include <map>


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

int Lib_Image::initialize(InitLibs init)
{
    static std::map<InitLibs, int>  mapToSDLImageLibs =
    {
        {ImageJpg,  IMG_INIT_JPG},
        {ImagePng,  IMG_INIT_PNG},
        {ImageTif,  IMG_INIT_TIF},
        {ImageWebp, IMG_INIT_WEBP},
        {ImageJxl,  IMG_INIT_JXL},
        {ImageAvif, IMG_INIT_AVIF}
    };
    int flags   = 0;
    for (auto const& item: mapToSDLImageLibs)
    {
        if (item.first & init) {
            flags |= item.second;
        }
    }
    int initValue  = IMG_Init(flags);
    // Note: IMG_Init is not symmetric.
    //       A failure here will cause an exception to be thrown
    //       which will prevent the destructor not to be called.
    //
    //       IMG_Init() may init some img-sub-systems but this function
    //       will fail if not all requested img-sub-systems are correctly initialized.
    //       so we need call IMG_Quit() to make sure that it is tidied up correctly.
    int result = (initValue & flags) == flags ? 0 : -1;
    if (result == -1) {
        IMG_Quit();
    }
    return result;
}

Lib_Image::Lib_Image(InitLibs init)
    : BaseWrapper(initialize(init), "Failed to Initialize SDL2 Image")
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
