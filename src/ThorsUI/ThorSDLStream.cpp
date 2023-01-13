#include "ThorSDLStream.h"
#include "Surface.h"
#include <SDL_image.h>

extern "C"
{
    static Sint64 streamSizeThor(SDL_RWops*);
    static Sint64 streamSeekThorRead(SDL_RWops*, Sint64, int);
    static Sint64 streamSeekThorWrite(SDL_RWops*, Sint64, int);
    static size_t streamReadThor(SDL_RWops*, void*, size_t, size_t);
    static size_t streamReadThorBad(SDL_RWops*, void*, size_t, size_t);
    static size_t streamWriteThor(SDL_RWops*, const void*, size_t, size_t);
    static size_t streamWriteThorBad(SDL_RWops*, const void*, size_t, size_t);
    static int streamCloseThor(SDL_RWops*);
}

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

/*
 * The SDL_RWops Seek calls this function.
 * This is used to reset the stream to the clean state when things
 * go wrong (such as when trying to discover file format).
 *
 * The result is the offset into the file after the seek is done.
 *
 * The code use TELL => SEEK(CUR, 0)
 */
Sint64 streamSeekThorRead(SDL_RWops* input, Sint64 dist, int dir)
{
    ThorSDLStreamRead*  data = static_cast<ThorSDLStreamRead*>(input);
    data->stream.clear();
    std::ios_base::seekdir  direction = convertSDLDirectionThor(dir);
    data->stream.seekg(dist, direction);
    return data->stream ? static_cast<Sint64>(data->stream.tellg()) : -1;
}

/*
 * Like streamSeekThorRead but uses write stream.
 */
Sint64 streamSeekThorWrite(SDL_RWops* output, Sint64 dist, int dir)
{
    ThorSDLStreamWrite*  data = static_cast<ThorSDLStreamWrite*>(output);
    data->stream.clear();
    std::ios_base::seekdir  direction = convertSDLDirectionThor(dir);
    data->stream.seekp(dist, direction);
    return data->stream ? static_cast<Sint64>(data->stream.tellp()) : -1;
}

/*
 * Reads `num` objects of size `size` from the stream.
 * Return the number of objects read.
 */
size_t streamReadThor(SDL_RWops* input, void* dst, size_t size, size_t num)
{
    ThorSDLStreamRead*  data = static_cast<ThorSDLStreamRead*>(input);
    data->stream.read(reinterpret_cast<char*>(dst), num * size);
    return data->stream.gcount() / size;
}

/*
 * Write `num` objects of size `size` to the stream.
 * Return -1 on failure or the number of objects written.
 */
size_t streamWriteThor(SDL_RWops* output, const void* src, size_t size, size_t num)
{
    ThorSDLStreamWrite*  data = static_cast<ThorSDLStreamWrite*>(output);

    if (!data->stream) {
        return 0;
    }

    auto before = data->stream.tellp();
    data->stream.write(reinterpret_cast<char const*>(src), num * size);
    return (data->stream.tellp() - before) / size;
}

/* Functionality that does not make sense for this implementation */
int     streamCloseThor(SDL_RWops*)                                 {return 0;}
Sint64  streamSizeThor(SDL_RWops*)                                  {return -1;}
size_t  streamReadThorBad(SDL_RWops*, void*, size_t, size_t)        {return -1;}
size_t  streamWriteThorBad(SDL_RWops*, const void*, size_t, size_t) {return -1;}

// Set up a read object.
ThorSDLStreamRead::ThorSDLStreamRead(std::istream& stream)
    : stream(stream)
{
    // Useful
    seek    = streamSeekThorRead;
    read    = streamReadThor;
    type    = SDL_RWOPS_UNKNOWN;

    // Does nothing
    write   = streamWriteThorBad;
    size    = streamSizeThor;
    close   = streamCloseThor;
}

// Set up a write object.
ThorSDLStreamWrite::ThorSDLStreamWrite(std::ostream& stream)
    : stream(stream)
{
    // Useful
    seek    = streamSeekThorWrite;
    write   = streamWriteThor;
    type    = SDL_RWOPS_UNKNOWN;

    // Does nothing
    read    = streamReadThorBad;
    size    = streamSizeThor;
    close   = streamCloseThor;
}
