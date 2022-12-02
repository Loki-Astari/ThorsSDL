#ifndef THORSANVIL_UI_DRAW_CONTEXT_H
#define THORSANVIL_UI_DRAW_CONTEXT_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"
#include <gtest/gtest_prod.h>
#include <iostream>

class DrawContextTest_GetSurface_Test;
namespace ThorsAnvil::UI
{

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
        DrawContext(DrawContext&& move)             noexcept;
        DrawContext& operator=(DrawContext&& move)  noexcept;

    private:
        void destroy();
    private:
        friend class Pen;
        friend class TextPen;
        friend class Texture;
        friend class Window;
        FRIEND_TEST(::DrawContextTest, GetSurface);
        SDL_Renderer* getRenderer() const {return renderer.get() ? *renderer : nullptr;}
    private:
        std::unique_ptr<SDL::Renderer>   renderer;
};

}

#endif
