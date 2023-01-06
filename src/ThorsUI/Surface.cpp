#include "Surface.h"
#include <SDL_image.h>

std::ios_base::seekdir convertSDLDirectionThor(int dir)
{
    switch (dir)
    {
        case RW_SEEK_SET:   return std::ios_base::beg;
        case RW_SEEK_CUR:   return std::ios_base::cur;
        case RW_SEEK_END:   return std::ios_base::end;
    }
    return std::ios_base::beg;
}

Sint64 streamSeekThorRead(SDL_RWops* input, Sint64 dist, int dir)
{
    ThorsSDLRWopsRead*  data = reinterpret_cast<ThorsSDLRWopsRead*>(input);
    data->stream.clear();
    std::ios_base::seekdir  direction = convertSDLDirectionThor(dir);
    data->stream.seekg(dist, direction);
    return data->stream ? 0 : -1;
}

Sint64 streamSeekThorWrite(SDL_RWops* input, Sint64 dist, int dir)
{
    ThorsSDLRWopsWrite*  data = reinterpret_cast<ThorsSDLRWopsWrite*>(input);
    data->stream.clear();
    std::ios_base::seekdir  direction = convertSDLDirectionThor(dir);
    data->stream.seekp(dist, direction);
    return data->stream ? 0 : -1;
}

size_t streamReadThor(SDL_RWops* input, void* dst, size_t size, size_t num)
{
    ThorsSDLRWopsRead*  data = reinterpret_cast<ThorsSDLRWopsRead*>(input);
    data->stream.read(reinterpret_cast<char*>(dst), num * size);
    return data->stream ? data->stream.gcount() / size : -1;
}

size_t streamWriteThor(SDL_RWops* input, const void* src, size_t size, size_t num)
{
    ThorsSDLRWopsWrite*  data = reinterpret_cast<ThorsSDLRWopsWrite*>(input);
    auto before = data->stream.tellp();

    data->stream.write(reinterpret_cast<char const*>(src), num * size);
    return data->stream ? (data->stream.tellp() - before) / size : -1;
}

int     streamCloseThor(SDL_RWops*)                                 {return 0;}
Sint64  streamSizeThor(SDL_RWops*)                                  {return -1;}
size_t  streamReadThorBad(SDL_RWops*, void*, size_t, size_t)        {return -1;}
size_t  streamWriteThorBad(SDL_RWops*, const void*, size_t, size_t) {return -1;}

ThorsSDLRWopsRead::ThorsSDLRWopsRead(std::istream& stream)
    : stream(stream)
{
    seek    = streamSeekThorRead;
    read    = streamReadThor;
    type    = SDL_RWOPS_UNKNOWN;
    close   = streamCloseThor;

    //
    write   = streamWriteThorBad;
    size    = streamSizeThor;
}
ThorsSDLRWopsWrite::ThorsSDLRWopsWrite(std::ostream& stream)
    : stream(stream)
{
    seek    = streamSeekThorWrite;
    write   = streamWriteThor;
    type    = SDL_RWOPS_UNKNOWN;
    close   = streamCloseThor;

    //
    read    = streamReadThorBad;
    size    = streamSizeThor;
}

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
            ThorsSDLRWopsRead   streamWrapper(stream);
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
        ThorsSDLRWopsWrite  streamWrapper(stream);
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
        ThorsSDLRWopsWrite  streamWrapper(stream);
        int status = IMG_SaveJPG_RW(surface.surface, &streamWrapper, 0, quality);
        if (status != 0) {
            stream.setstate(std::ios::failbit);
        }
    }
    return stream;
}
