#include "Surface.h"
#include "ThorSDLStream.h"
#include <SDL_image.h>

using namespace ThorsAnvil::UI;

Surface::Surface()
    : surface()
{}

Surface::Surface(SDL::Surface&& surface)
    : surface(std::move(surface))
{}

std::istream& Surface::loadFromStream(std::istream& stream)
{
    if (stream)
    {
        try
        {
            ThorSDLStreamRead   streamWrapper(stream);
            SDL_Surface*        newSurface = IMG_Load_RW(&streamWrapper, 0);
            SDL::Surface        tmp(newSurface, "Failed to load image from stream");
            std::swap(surface, tmp);
        }
        catch (std::exception const& e)
        {
            stream.setstate(std::ios::failbit);
            std::cerr << "Stream Error: " << e.what() << "\n";
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
        int status = IMG_SavePNG_RW(surface.surface, &streamWrapper, 0);
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
        int status = IMG_SaveJPG_RW(surface.surface, &streamWrapper, 0, quality);
        if (status != 0) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}
