#ifndef THORSANVIL_UI_TEXTURE_H
#define THORSANVIL_UI_TEXTURE_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"
#include "Util.h"

namespace ThorsAnvil::UI
{

static constexpr Rect   zero{0, 0, 0, 0};

class TextPen;
class DrawContext;
class Texture
{
    DrawContext&                    drawContext;
    std::shared_ptr<SDL_Texture>    texture;

    private:
        friend class TextPen;
        Texture(DrawContext& drawContext, SDL_Surface& surface);
    public:

        void doDraw(Rect dst = zero, Rect src = zero);
};

}

#endif
