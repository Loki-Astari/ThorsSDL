#ifndef THORSANVIL_UI_PEN_H
#define THORSANVIL_UI_PEN_H

#include "ThorsSDLConfig.h"
#include "Util.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace ThorsAnvil::UI
{

/* Notes:
    1: SDL_RenderClear      before drawing.
    2: SDL_RenderPresent    After drawing.

    SDL_RenderCopy:         Copies Texture to render
    SDL_RenderCopyEx:       Copies Texture to render with translation

    SDL_GetRenderDrawBlendMode / SDL_SetRenderDrawBlendMode

    Render Information:
        SDL_RenderGetClipRect       SDL_RenderSetClipRect       SDL_RenderIsClipEnabled


    Size Information:
        SDL_GetRendererOutputSize / SDL_GetWindowSize

    SCalingInformation:
        SDL_RenderLogicalToWindow / SDL_RenderWindowToLogical

            SDL_RenderGetScale          SDL_RenderSetScale
            SDL_RenderGetLogicalSize    SDL_RenderSetLogicalSize
    Info:
        SDL_GetRendererInfo
    Obscure Info:
        SDL_RenderGetIntegerScale   SDL_RenderSetIntegerScale
        SDL_RenderGetViewport       SDL_RenderSetViewport
        SDL_GetRenderTarget         SDL_SetRenderTarget
        SDL_RenderGetWindow         SDL_GetRenderer
    Slow:
        SDL_RenderReadPixels


    Device Info:
        SDL_GetNumRenderDrivers
        SDL_GetRenderDriverInfo
        SDL_RenderGetD3D11Device    SDL_RenderGetD3D12Device    SDL_RenderGetD3D9Device
        SDL_RenderGetMetalCommandEncodera
        SDL_RenderGetMetalLayer
        SDL_RenderSetVSyc

        SDL_SetRenderTarget
        SDL_RenderTargetSupported
*/

class DrawContext;
class Pen
{
    public:
        Pen(Color ink =  {0, 0, 0, 255}, Color fill = {255, 255, 255, 0});

        Color           ink     = {0, 0, 0, 255};       // Solid Black
        Color           fill    = {255, 255, 255, 0};   // Transparent (White)

    public:
        // Basic Drawing
        void drawPoint(DrawContext& drawContext, Pt const& point) const;                     // SDL_RenderDrawPoint
        void drawLine(DrawContext& drawContext, Pt const& start, Pt const& end) const;       // SDL_RenderDrawLine
        void drawRect(DrawContext& drawContext, Rect const& rect) const;                     // SDL_RenderDrawRect / SDL_RenderFillRect

        void drawPoints(DrawContext& drawContext, std::initializer_list<Pt> points) const;   // SDL_RenderDrawPoints
        void drawLines(DrawContext& drawContext, std::initializer_list<Pt> points) const;    // SDL_RenderDrawLines
        void drawRects(DrawContext& drawContext, std::initializer_list<Rect> rects) const;   // SDL_RenderDrawRects / SDL_RenderFillRects

        // Advanced Drawing
        // void drawGeometry: SDL_RenderGeometry
};

class TextPen: public Pen
{
    public:
        TextPen(std::string const& fontName, int pt = 12, Color ink =  {0, 0, 0, 255}, Color fill = {255, 255, 255, 0});

    private:
        std::shared_ptr<TTF_Font>   font;
};


}

#endif
