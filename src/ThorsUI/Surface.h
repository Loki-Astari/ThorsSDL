#ifndef THORSANVIL_UI_SURFACE_H
#define THORSANVIL_UI_SURFACE_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"

namespace ThorsAnvil::UI
{

class SurfaceToPNG;
class SurfaceToJPG;
class Surface
{
    friend class SurfaceToPNG;
    friend class SurfaceToJPG;
    friend class Texture;
    SDL::Surface    surface;
    public:
        Surface();
        Surface(SDL::Surface&& surface);

    private:
        std::istream& loadFromStream(std::istream& stream);
        std::ostream& saveToStream(std::ostream& stream) const;

        friend std::istream& operator>>(std::istream& stream, Surface& dst)         {return dst.loadFromStream(stream);}
        friend std::ostream& operator<<(std::ostream& stream, Surface const&)
        {
            static_assert(true, "Can not output Surface to stream. You need to specify an output type use SurfaceToPNG/SurfaceToJPG wrappers");
            return stream;
        }
};

class SurfaceToPNG
{
    Surface&    surface;
    public:
        SurfaceToPNG(Surface& surface);
        std::ostream& saveToStream(std::ostream& stream) const;
        friend std::ostream& operator<<(std::ostream& stream, SurfaceToPNG const& src)   {return src.saveToStream(stream);}
};

class SurfaceToJPG
{
    Surface&    surface;
    int         quality;
    public:
        SurfaceToJPG(Surface& surface, int quality = 80);
        std::ostream& saveToStream(std::ostream& stream) const;
        friend std::ostream& operator<<(std::ostream& stream, SurfaceToJPG const& src)   {return src.saveToStream(stream);}
};

}

#endif
