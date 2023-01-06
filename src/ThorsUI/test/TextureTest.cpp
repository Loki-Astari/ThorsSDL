#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "Texture.h"
#include "Application.h"
#include "Window.h"
#include "Pen.h"
#include "ThorsSDL.h"

TEST(TextureTest, TextureCreate)
{
    MocksSDLActions     actions;
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyTexture]);
}

TEST(TextureTest, TextureCreateWithSDL_CreateTextureFromSurfaceFailing)
{
    MocksSDLActions     actions{.mockSDL_CreateTextureFromSurface = [](SDL_Renderer*, SDL_Surface*) ->SDL_Texture*{return nullptr;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(0, actions.count[countSDL_DestroyTexture]);
}

TEST(TextureTest, TextureDrawCalcSrcCalcDst)
{
    int srcRectIsNull = 0;
    MocksSDLActions     actions{.mockSDL_RenderCopy = [&srcRectIsNull](SDL_Renderer*, SDL_Texture*, SDL_Rect const* src, SDL_Rect const*){srcRectIsNull = src == nullptr ? 1 : 2;return 0;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 

        texture.draw({0,0,0,0},{0,0,0,0});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyTexture]);
    EXPECT_EQ(1, actions.count[countSDL_QueryTexture]);
    EXPECT_EQ(1, actions.count[countSDL_RenderCopy]);
    EXPECT_EQ(1, srcRectIsNull);
}

TEST(TextureTest, TextureDrawSpecSrcCalcDst)
{
    int srcRectIsNull = 0;
    MocksSDLActions     actions{.mockSDL_RenderCopy = [&srcRectIsNull](SDL_Renderer*, SDL_Texture*, SDL_Rect const* src, SDL_Rect const*){srcRectIsNull = src == nullptr ? 1 : 2;return 0;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 

        texture.draw({0,0,0,0},{0,0,10,10});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyTexture]);
    EXPECT_EQ(1, actions.count[countSDL_QueryTexture]);
    EXPECT_EQ(1, actions.count[countSDL_RenderCopy]);
    EXPECT_EQ(2, srcRectIsNull);
}

TEST(TextureTest, TextureDrawCalcSrcSpecDst)
{
    int srcRectIsNull = 0;
    MocksSDLActions     actions{.mockSDL_RenderCopy = [&srcRectIsNull](SDL_Renderer*, SDL_Texture*, SDL_Rect const* src, SDL_Rect const*){srcRectIsNull = src == nullptr ? 1 : 2;return 0;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 

        texture.draw({0,0,10,10},{0,0,0,0});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyTexture]);
    EXPECT_EQ(0, actions.count[countSDL_QueryTexture]);
    EXPECT_EQ(1, actions.count[countSDL_RenderCopy]);
    EXPECT_EQ(1, srcRectIsNull);
}

TEST(TextureTest, TextureDrawSpecSrcSpecDst)
{
    int srcRectIsNull = 0;
    MocksSDLActions     actions{.mockSDL_RenderCopy = [&srcRectIsNull](SDL_Renderer*, SDL_Texture*, SDL_Rect const* src, SDL_Rect const*){srcRectIsNull = src == nullptr ? 1 : 2;return 0;}};
    MockSDL             mockActivate(actions);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window("Title", {100, 100, 200, 200});
        ThorsAnvil::UI::TextPen         pen("filename", 12);

        ThorsAnvil::UI::Texture         texture = pen.createTextureFromString(window, "Message"); 

        texture.draw({0,0,10,10},{0,0,10,10});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, actions.count[countSDL_CreateTextureFromSurface]);
    EXPECT_EQ(1, actions.count[countSDL_DestroyTexture]);
    EXPECT_EQ(0, actions.count[countSDL_QueryTexture]);
    EXPECT_EQ(1, actions.count[countSDL_RenderCopy]);
    EXPECT_EQ(2, srcRectIsNull);
}

