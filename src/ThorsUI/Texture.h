#ifndef THORSANVIL_UI_TEXTURE_H
#define THORSANVIL_UI_TEXTURE_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"
#include "Util.h"
#include <gtest/gtest_prod.h>
#include <memory>

class TextureTest_TextureCreate_Test;
class TextureTest_TextureCreateWithSDL_CreateTextureFromSurfaceFailing_Test;
class TextureTest_TextureDrawCalcSrcCalcDst_Test;
class TextureTest_TextureDrawCalcSrcSpecDst_Test;
class TextureTest_TextureDrawSpecSrcCalcDst_Test;
class TextureTest_TextureDrawSpecSrcSpecDst_Test;
namespace ThorsAnvil::UI
{

static constexpr Rect   zero{0, 0, 0, 0};

class TextPen;
class DrawContext;
class Surface;
class Texture
{
    DrawContext*                    drawContext;
    std::shared_ptr<SDL_Texture>    texture;

    private:
        FRIEND_TEST(::TextureTest, TextureCreate);
        FRIEND_TEST(::TextureTest, TextureCreateWithSDL_CreateTextureFromSurfaceFailing);
        FRIEND_TEST(::TextureTest, TextureDrawCalcSrcCalcDst);
        FRIEND_TEST(::TextureTest, TextureDrawSpecSrcCalcDst);
        FRIEND_TEST(::TextureTest, TextureDrawCalcSrcSpecDst);
        FRIEND_TEST(::TextureTest, TextureDrawSpecSrcSpecDst);

    public:
        Texture();
        Texture(Texture& copy)              = default;
        Texture(Texture&& move)             = default;
        Texture(DrawContext& drawContext, Surface& surface);

        Texture& operator=(Texture& copt)   = default;
        Texture& operator=(Texture&& move)  = default;

        Sz size() const;
        bool valid() const;
        void draw(Rect dst = zero, Rect src = zero) const;
        void reset();
};

}

#endif
