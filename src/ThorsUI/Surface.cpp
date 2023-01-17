#include "Surface.h"
#include "ThorSDLStream.h"
#include <SDL_image.h>

using namespace ThorsAnvil::UI;

Surface::Surface()
    : sdlSurface(nullptr)
{}

Surface::Surface(SDL_Surface* sdlSurface, char const* errorMessage)
    : sdlSurface(sdlSurface)
{
    if (sdlSurface == nullptr) {
        throw std::runtime_error(errorMessage);
    }
}

Surface::Surface(Surface&& src) noexcept
    : sdlSurface(std::exchange(src.sdlSurface, nullptr))
{}

Surface& Surface::operator=(Surface&& src) noexcept
{
    SDL_FreeSurface(sdlSurface);
    sdlSurface = std::exchange(src.sdlSurface, nullptr);
    return *this;
}

Surface::~Surface()
{
    if (sdlSurface) {
        SDL_FreeSurface(sdlSurface);
    }
}

void Surface::swap(Surface& other) noexcept
{
    std::swap(sdlSurface, other.sdlSurface);
}

std::istream& Surface::loadFromStream(std::istream& stream)
{
    if (stream)
    {
        try
        {
            ThorSDLStreamRead   streamWrapper(stream);
            Surface             tmp(IMG_Load_RW(&streamWrapper, 0), "Failed to Create SDL-Surface from image file.");
            swap(tmp);
        }
        catch (std::exception const& e)
        {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}

SurfaceToPNG::SurfaceToPNG(Surface& surface)
    : surface(surface)
{}

std::ostream& SurfaceToPNG::saveToStream(std::ostream& stream) const
{
    if (stream)
    {
        ThorSDLStreamWrite  streamWrapper(stream);
        int status = IMG_SavePNG_RW(surface.sdlSurface, &streamWrapper, 0);
        if (status != 0) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
};

SurfaceToJPG::SurfaceToJPG(Surface& surface, int quality)
    : surface(surface)
    , quality(quality)
{}

std::ostream& SurfaceToJPG::saveToStream(std::ostream& stream) const
{
    if (stream)
    {
        ThorSDLStreamWrite  streamWrapper(stream);
        int status = IMG_SaveJPG_RW(surface.sdlSurface, &streamWrapper, 0, quality);
        if (status != 0) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}
