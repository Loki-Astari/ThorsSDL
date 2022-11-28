#ifndef THORSANVIL_UI_DRAW_CONTEXT_H
#define THORSANVIL_UI_DRAW_CONTEXT_H

#include "ThorsSDLConfig.h"
#include <SDL.h>
#include <gtest/gtest_prod.h>
#include <iostream>

class DrawContextTest_GetSurface_Test;
namespace ThorsAnvil::UI
{

/*
Renderer Flags:
===============
    SDL_RENDERER_SOFTWARE         The renderer is a software fallback
    SDL_RENDERER_ACCELERATED      The renderer uses hardware acceleration
    SDL_RENDERER_PRESENTVSYNC     Present is synchronized with the refresh rate
    SDL_RENDERER_TARGETTEXTURE    The renderer supports rendering to text
*/

struct RenderState
{
    bool    software    = false;
    bool    accelerated = true;
    bool    presentSync = false;
    bool    targetText  = false;

    operator Uint32 () const;

    friend std::ostream& operator<<(std::ostream& s, RenderState const& rs)
    {
        return s    << "{\n"
                    << "Software:    " << rs.software       << " " << (rs.software ? SDL_RENDERER_SOFTWARE : 0)        << "\n"
                    << "accelerated: " << rs.accelerated    << " " << (rs.accelerated ? SDL_RENDERER_ACCELERATED : 0)  << "\n"
                    << "presentSync: " << rs.presentSync    << " " << (rs.presentSync ? SDL_RENDERER_PRESENTVSYNC : 0) << "\n"
                    << "targetText:  " << rs.targetText     << " " << (rs.targetText ? SDL_RENDERER_TARGETTEXTURE : 0) << "\n"
                    << "}";
    }
};

class Window;
class Pen;
class TextPen;
class Texture;
class DrawContext
{
    public:
        DrawContext(SDL_Window* sdlWindow = nullptr, RenderState const& renState = {});
        ~DrawContext();

        DrawContext(DrawContext const&)             = delete;
        DrawContext& operator=(DrawContext const&)  = delete;
        DrawContext(DrawContext&& move) noexcept;
        DrawContext& operator=(DrawContext&& move) noexcept;

    private:
        void destroy();
    private:
        friend class Pen;
        friend class TextPen;
        friend class Texture;
        friend class Window;
        FRIEND_TEST(::DrawContextTest, GetSurface);
        SDL_Renderer* getSurface() const {return renderer;}
    private:
        SDL_Renderer*   renderer;
};

}

#endif
