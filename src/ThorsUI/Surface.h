#ifndef THORSANVIL_UI_SURFACE_H
#define THORSANVIL_UI_SURFACE_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"

extern "C"
{
    Sint64 streamSizeThors(SDL_RWops*);
    Sint64 streamSeekThorRead(SDL_RWops*, Sint64, int);
    Sint64 streamSeekThorWrite(SDL_RWops*, Sint64, int);
    size_t streamReadThor(SDL_RWops*, void*, size_t, size_t);
    size_t streamReadThorBad(SDL_RWops*, void*, size_t, size_t);
    size_t streamWriteThor(SDL_RWops*, const void*, size_t, size_t);
    size_t streamWriteThorBad(SDL_RWops*, const void*, size_t, size_t);
    int streamCloseThor(SDL_RWops*);
}

struct ThorsSDLRWopsRead: public SDL_RWops
{
    std::istream&   stream;

    ThorsSDLRWopsRead(std::istream& stream);
};
struct ThorsSDLRWopsWrite: public SDL_RWops
{
    std::ostream&   stream;

    ThorsSDLRWopsWrite(std::ostream& stream);
};

namespace ThorsAnvil::UI
{

class SurfaceToPNG;
class SurfaceToJPG;
class Surface
{
    friend class SurfaceToPNG;
    friend class SurfaceToJPG;
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
