#include "test/WindowTest.h"

TEST(WindowTest, WindowConstruction)
{
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});
    MOCK_SYS(SDL_Quit,        [](){});
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event*){return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return reinterpret_cast<SDL_Window*>(createWindow);};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return reinterpret_cast<SDL_Renderer*>(createRender);};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window* win) -> Uint32 {++windowId;return reinterpret_cast<std::uintptr_t>(win);};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, createWindow);
    EXPECT_EQ(1, destroyWindow);
    EXPECT_EQ(1, createRender);
    EXPECT_EQ(1, destroyRender);
    EXPECT_EQ(2, windowId);
}

TEST(WindowTest, WindowConstruction_WindowCreateFails)
{
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});
    MOCK_SYS(SDL_Quit,        [](){});
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event*){return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return nullptr;};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return reinterpret_cast<SDL_Renderer*>(createRender);};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window* win) -> Uint32 {++windowId;return reinterpret_cast<std::uintptr_t>(win);};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, createWindow);
    EXPECT_EQ(0, destroyWindow);
    EXPECT_EQ(0, createRender);
    EXPECT_EQ(0, destroyRender);
    EXPECT_EQ(0, windowId);
}

TEST(WindowTest, WindowConstruction_RenderCreateFails)
{
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});
    MOCK_SYS(SDL_Quit,        [](){});
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event*){return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return reinterpret_cast<SDL_Window*>(createWindow);};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return nullptr;};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window* win) -> Uint32 {++windowId;return reinterpret_cast<std::uintptr_t>(win);};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          window(application, "Title", {100, 100, 200, 200});
    };

    EXPECT_THROW(
        action(),
        std::runtime_error
    );

    EXPECT_EQ(1, createWindow);
    EXPECT_EQ(1, destroyWindow);
    EXPECT_EQ(1, createRender);
    EXPECT_EQ(0, destroyRender);
    EXPECT_EQ(0, windowId);
}

TEST(WindowTest, WindowMoveConstruction)
{
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});
    MOCK_SYS(SDL_Quit,        [](){});
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event*){return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return reinterpret_cast<SDL_Window*>(createWindow);};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return reinterpret_cast<SDL_Renderer*>(createRender);};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window* win) -> Uint32 {++windowId;return reinterpret_cast<std::uintptr_t>(win);};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src(application, "Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst(std::move(src));
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(1, createWindow);
    EXPECT_EQ(1, destroyWindow);
    EXPECT_EQ(1, createRender);
    EXPECT_EQ(1, destroyRender);
    EXPECT_EQ(3, windowId);
}

TEST(WindowTest, WindowMoveAssignment)
{
    MOCK_SYS(SDL_Init,        [](Uint32){return 0;});
    MOCK_SYS(SDL_Quit,        [](){});
    MOCK_SYS(SDL_PollEvent,   [](SDL_Event*){return 0;});

    int createWindow = 0;
    int createRender = 0;
    int destroyWindow = 0;
    int destroyRender = 0;
    int windowId = 0;
    auto createWindowMock       = [&createWindow](char const*, Uint32, Uint32, Uint32, Uint32, Uint32) -> SDL_Window* {++createWindow;return reinterpret_cast<SDL_Window*>(createWindow);};
    auto destroyWindowMock      = [&destroyWindow](SDL_Window*){++destroyWindow;};
    auto createRendererMock     = [&createRender](SDL_Window*, Uint32, Uint32) -> SDL_Renderer* {++createRender;return reinterpret_cast<SDL_Renderer*>(createRender);};
    auto destroyRendererMock    = [&destroyRender](SDL_Renderer*){++destroyRender;};
    auto setHintMock            = [](char const*, char const*) { return  SDL_TRUE;}; // SDL_FALSE on not working
    auto setRenderDrawColorMock = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){ return 0;}; // -1 failure
    auto renderClearMock        = [](SDL_Renderer*){ return 0;}; // -1 failure.
    auto renderPresentMock      = [](SDL_Renderer*){};
    auto getWindowIdMock        = [&windowId](SDL_Window* win) -> Uint32 {++windowId;return reinterpret_cast<std::uintptr_t>(win);};

    MOCK_SYS(SDL_CreateWindow,      createWindowMock);
    MOCK_SYS(SDL_DestroyWindow,     destroyWindowMock);
    MOCK_SYS(SDL_CreateRenderer,    createRendererMock);
    MOCK_SYS(SDL_DestroyRenderer,   destroyRendererMock);
    MOCK_SYS(SDL_SetHint,           setHintMock);
    MOCK_SYS(SDL_SetRenderDrawColor,setRenderDrawColorMock);
    MOCK_SYS(SDL_RenderClear,       renderClearMock);
    MOCK_SYS(SDL_RenderPresent,     renderPresentMock);
    MOCK_SYS(SDL_GetWindowID,       getWindowIdMock);

    auto action = []()
    {
        ThorsAnvil::UI::Application     application;
        ThorsAnvil::UI::Window          src(application, "Title", {100, 100, 200, 200});
        ThorsAnvil::UI::Window          dst(application, "Next", {20, 20, 10, 10});

        dst = std::move(src);
    };

    EXPECT_NO_THROW(
        action();
    );

    EXPECT_EQ(2, createWindow);
    EXPECT_EQ(2, destroyWindow);
    EXPECT_EQ(2, createRender);
    EXPECT_EQ(2, destroyRender);
    EXPECT_EQ(5, windowId);
}

