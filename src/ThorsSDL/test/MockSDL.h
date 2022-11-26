#ifndef THORSANVIL_UI_TEST_MOCK_SDL_H
#define THORSANVIL_UI_TEST_MOCK_SDL_H

#include "coverage/ThorMock.h"
#include <functional>

struct MocksSDLActions
{
    int     countSDL_Init               = 0;
    int     countSDL_Quit               = 0;
    int     countSDL_InitSubSystem      = 0;
    int     countSDL_QuitSubSystem      = 0;
    int     countSDL_CreateWindow       = 0;
    int     countSDL_DestroyWindow      = 0;
    int     countSDL_CreateRenderer     = 0;
    int     countSDL_DestroyRenderer    = 0;
    int     countSDL_PollEvent          = 0;
    int     countSDL_SetHint            = 0;
    int     countSDL_SetRenderDrawColor = 0;
    int     countSDL_RenderClear        = 0;
    int     countSDL_RenderPresent      = 0;
    int     countSDL_GetWindowID        = 0;
    int     countSDL_RenderDrawPoint    = 0;
    int     countSDL_RenderDrawPoints   = 0;
    int     countSDL_RenderDrawLine     = 0;
    int     countSDL_RenderDrawLines    = 0;
    int     countSDL_RenderFillRect     = 0;
    int     countSDL_RenderDrawRect     = 0;
    int     countSDL_RenderFillRects    = 0;
    int     countSDL_RenderDrawRects    = 0;

    std::function<int(Uint32)>                                          mockSDL_Init                = [](Uint32){return 0;};
    std::function<void()>                                               mockSDL_Quit                = [](){};
    std::function<int(Uint32)>                                          mockSDL_InitSubSystem       = [](Uint32){return 0;};
    std::function<void(Uint32)>                                         mockSDL_QuitSubSystem       = [](Uint32){};
    std::function<SDL_Window*(char const*, int, int, int, int, Uint32)> mockSDL_CreateWindow        = [](char const*, int, int, int, int, Uint32) -> SDL_Window*
    {
        static int winNumber = 0;
        ++winNumber;
        std::cerr << "Created: " << winNumber << "\n";
        return reinterpret_cast<SDL_Window*>(winNumber);
    };
    std::function<void(SDL_Window*)>                                    mockSDL_DestroyWindow       = [](SDL_Window*){};
    std::function<SDL_Renderer*(SDL_Window*, int, Uint32)>              mockSDL_CreateRenderer      = [](SDL_Window*, int, Uint32) -> SDL_Renderer*
    {
        static int renNumber = 0;
        ++renNumber;
        return reinterpret_cast<SDL_Renderer*>(2000 + renNumber);
    };
    std::function<void(SDL_Renderer*)>                                  mockSDL_DestroyRenderer     = [](SDL_Renderer*){};
    std::function<int(SDL_Event*)>                                      mockSDL_PollEvent           = [](SDL_Event*){return 0;};
    std::function<SDL_bool(char const*, char const*)>                   mockSDL_SetHint             = [](char const*, char const*){return SDL_TRUE;};
    std::function<int(SDL_Renderer*, Uint8, Uint8, Uint8, Uint8)>       mockSDL_SetRenderDrawColor  = [](SDL_Renderer*, Uint8, Uint8, Uint8, Uint8){return 0;};
    std::function<int(SDL_Renderer*)>                                   mockSDL_RenderClear         = [](SDL_Renderer*){return 0;};
    std::function<void(SDL_Renderer*)>                                  mockSDL_RenderPresent       = [](SDL_Renderer*){};
    std::function<Uint32(SDL_Window*)>                                  mockSDL_GetWindowID         = [](SDL_Window* w) -> Uint32 {std::cerr << "Get: " << w << "\n";return reinterpret_cast<std::uintptr_t>(w);};
    std::function<int(SDL_Renderer*, int, int)>                         mockSDL_RenderDrawPoint     = [](SDL_Renderer*, int, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Point const*, int)>            mockSDL_RenderDrawPoints    = [](SDL_Renderer*, SDL_Point const*, int){return 0;};
    std::function<int(SDL_Renderer*, int, int, int, int)>               mockSDL_RenderDrawLine      = [](SDL_Renderer*, int, int, int, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Point const*, int)>            mockSDL_RenderDrawLines     = [](SDL_Renderer*, SDL_Point const*, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*)>                  mockSDL_RenderFillRect      = [](SDL_Renderer*, SDL_Rect const*){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*)>                  mockSDL_RenderDrawRect      = [](SDL_Renderer*, SDL_Rect const*){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*, int)>             mockSDL_RenderFillRects     = [](SDL_Renderer*, SDL_Rect const*, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*, int)>             mockSDL_RenderDrawRects     = [](SDL_Renderer*, SDL_Rect const*, int){return 0;};
};

class MockSDL
{
    MOCK_MEM_DECL(SDL_Init);
    MOCK_MEM_DECL(SDL_Quit);
    MOCK_MEM_DECL(SDL_InitSubSystem);
    MOCK_MEM_DECL(SDL_QuitSubSystem);
    MOCK_MEM_DECL(SDL_CreateWindow);
    MOCK_MEM_DECL(SDL_DestroyWindow);
    MOCK_MEM_DECL(SDL_CreateRenderer);
    MOCK_MEM_DECL(SDL_DestroyRenderer);
    MOCK_MEM_DECL(SDL_PollEvent);
    MOCK_MEM_DECL(SDL_SetHint);
    MOCK_MEM_DECL(SDL_SetRenderDrawColor);
    MOCK_MEM_DECL(SDL_RenderClear);
    MOCK_MEM_DECL(SDL_RenderPresent);
    MOCK_MEM_DECL(SDL_GetWindowID);
    MOCK_MEM_DECL(SDL_RenderDrawPoint);
    MOCK_MEM_DECL(SDL_RenderDrawPoints);
    MOCK_MEM_DECL(SDL_RenderDrawLine);
    MOCK_MEM_DECL(SDL_RenderDrawLines);
    MOCK_MEM_DECL(SDL_RenderFillRect);
    MOCK_MEM_DECL(SDL_RenderDrawRect);
    MOCK_MEM_DECL(SDL_RenderFillRects);
    MOCK_MEM_DECL(SDL_RenderDrawRects);

    public:
        MockSDL(MocksSDLActions& action)
            : MOCK_MEM_INIT(SDL_Init,               [&action](Uint32 f)                                             {++action.countSDL_Init;return action.mockSDL_Init(f);})
            , MOCK_MEM_INIT(SDL_Quit,               [&action]()                                                     {++action.countSDL_Quit;return action.mockSDL_Quit();})
            , MOCK_MEM_INIT(SDL_InitSubSystem,      [&action](Uint32 f)                                             {++action.countSDL_InitSubSystem;return action.mockSDL_InitSubSystem(f);})
            , MOCK_MEM_INIT(SDL_QuitSubSystem,      [&action](Uint32 f)                                             {++action.countSDL_QuitSubSystem;return action.mockSDL_QuitSubSystem(f);})
            , MOCK_MEM_INIT(SDL_CreateWindow,       [&action](char const* t, int x, int y, int w, int h, Uint32 f)  {++action.countSDL_CreateWindow;return action.mockSDL_CreateWindow(t, x, y, w, h, f);})
            , MOCK_MEM_INIT(SDL_DestroyWindow,      [&action](SDL_Window* w)                                        {++action.countSDL_DestroyWindow;return action.mockSDL_DestroyWindow(w);})
            , MOCK_MEM_INIT(SDL_CreateRenderer,     [&action](SDL_Window* w, int i, Uint32 f)                       {++action.countSDL_CreateRenderer;return action.mockSDL_CreateRenderer(w, i, f);})
            , MOCK_MEM_INIT(SDL_DestroyRenderer,    [&action](SDL_Renderer* r)                                      {++action.countSDL_DestroyRenderer;return action.mockSDL_DestroyRenderer(r);})
            , MOCK_MEM_INIT(SDL_PollEvent,          [&action](SDL_Event* e)                                         {++action.countSDL_PollEvent;return action.mockSDL_PollEvent(e);})
            , MOCK_MEM_INIT(SDL_SetHint,            [&action](char const* n, char const* v)                         {++action.countSDL_SetHint;return action.mockSDL_SetHint(n, v);})
            , MOCK_MEM_INIT(SDL_SetRenderDrawColor, [&action](SDL_Renderer* re, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {++action.countSDL_SetRenderDrawColor;return action.mockSDL_SetRenderDrawColor(re, r, g, b, a);})
            , MOCK_MEM_INIT(SDL_RenderClear,        [&action](SDL_Renderer* r)                                      {++action.countSDL_RenderClear;return action.mockSDL_RenderClear(r);})
            , MOCK_MEM_INIT(SDL_RenderPresent,      [&action](SDL_Renderer* r)                                      {++action.countSDL_RenderPresent;return action.mockSDL_RenderPresent(r);})
            , MOCK_MEM_INIT(SDL_GetWindowID,        [&action](SDL_Window* w)                                        {++action.countSDL_GetWindowID;return action.mockSDL_GetWindowID(w);})
            , MOCK_MEM_INIT(SDL_RenderDrawPoint,    [&action](SDL_Renderer* r, int x, int y)                        {++action.countSDL_RenderDrawPoint;return action.mockSDL_RenderDrawPoint(r, x, y);})
            , MOCK_MEM_INIT(SDL_RenderDrawPoints,   [&action](SDL_Renderer* r, SDL_Point const* p, int c)           {++action.countSDL_RenderDrawPoints;return action.mockSDL_RenderDrawPoints(r, p, c);})
            , MOCK_MEM_INIT(SDL_RenderDrawLine,     [&action](SDL_Renderer* r, int x1, int y1, int x2, int y2)      {++action.countSDL_RenderDrawLine;return action.mockSDL_RenderDrawLine(r, x1, x2, y1, y2);})
            , MOCK_MEM_INIT(SDL_RenderDrawLines,    [&action](SDL_Renderer* r, SDL_Point const* p, int c)           {++action.countSDL_RenderDrawLines;return action.mockSDL_RenderDrawLines(r, p, c);})
            , MOCK_MEM_INIT(SDL_RenderFillRect,     [&action](SDL_Renderer* r, SDL_Rect const* rp)                  {++action.countSDL_RenderFillRect;return action.mockSDL_RenderFillRect(r, rp);})
            , MOCK_MEM_INIT(SDL_RenderDrawRect,     [&action](SDL_Renderer* r, SDL_Rect const* rp)                  {++action.countSDL_RenderDrawRect;return action.mockSDL_RenderDrawRect(r, rp);})
            , MOCK_MEM_INIT(SDL_RenderFillRects,    [&action](SDL_Renderer* r, SDL_Rect const* rp, int c)           {++action.countSDL_RenderFillRects;return action.mockSDL_RenderFillRects(r, rp, c);})
            , MOCK_MEM_INIT(SDL_RenderDrawRects,    [&action](SDL_Renderer* r, SDL_Rect const* rp, int c)           {++action.countSDL_RenderDrawRects;return action.mockSDL_RenderDrawRects(r, rp, c);})
        {}

};

#endif
