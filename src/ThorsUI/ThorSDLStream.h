#ifndef THORSANVIL_UI_THOR_SDL_STREAM_H
#define THORSANVIL_UI_THOR_SDL_STREAM_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"

struct ThorSDLStreamRead: public SDL_RWops
{
    std::istream&   stream;

    ThorSDLStreamRead(std::istream& stream);
};
struct ThorSDLStreamWrite: public SDL_RWops
{
    std::ostream&   stream;

    ThorSDLStreamWrite(std::ostream& stream);
};

#endif
