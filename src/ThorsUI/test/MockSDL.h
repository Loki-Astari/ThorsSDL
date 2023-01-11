#ifndef THORSANVIL_UI_TEST_MOCK_SDL_H
#define THORSANVIL_UI_TEST_MOCK_SDL_H

#include "coverage/ThorMock.h"
#include <functional>
#include <numeric>

enum {
      countSDL_Init
    , countSDL_Quit
    , countSDL_InitSubSystem
    , countSDL_QuitSubSystem
    , countSDL_CreateWindow
    , countSDL_DestroyWindow
    , countSDL_CreateRenderer
    , countSDL_DestroyRenderer
    , countSDL_PollEvent
    , countSDL_SetHint
    , countSDL_SetRenderDrawColor
    , countSDL_RenderClear
    , countSDL_RenderPresent
    , countSDL_GetWindowID
    , countSDL_RenderDrawPoint
    , countSDL_RenderDrawPoints
    , countSDL_RenderDrawLine
    , countSDL_RenderDrawLines
    , countSDL_RenderFillRect
    , countSDL_RenderDrawRect
    , countSDL_RenderFillRects
    , countSDL_RenderDrawRects

    , countSDL_GetKeyboardState
    , countSDL_StartTextInput
    , countSDL_StopTextInput

    , countSDL_CreateTextureFromSurface
    , countSDL_DestroyTexture

    , countTTF_RenderText_Solid
    , countTTF_RenderUTF8_Solid
    , countSDL_FreeSurface

    , countSDL_QueryTexture
    , countSDL_RenderCopy

    , countTTF_Init
    , countTTF_Quit
    , countTTF_OpenFont
    , countTTF_CloseFont

    , countIMG_Init
    , countIMG_Quit
    , countIMG_Load_RW
    , countIMG_SavePNG_RW
    , countIMG_SaveJPG_RW

    , count_Max
};

struct MocksSDLActions
{
    int count[count_Max]    = {0};
    bool noSDLCalled()      {return std::accumulate(std::begin(count), std::end(count), 0) == 0;}

    std::function<int(Uint32)>                                          mockSDL_Init                = [](Uint32){return 0;};
    std::function<void()>                                               mockSDL_Quit                = [](){};
    std::function<int(Uint32)>                                          mockSDL_InitSubSystem       = [](Uint32){return 0;};
    std::function<void(Uint32)>                                         mockSDL_QuitSubSystem       = [](Uint32){};
    std::function<SDL_Window*(char const*, int, int, int, int, Uint32)> mockSDL_CreateWindow        = [](char const*, int, int, int, int, Uint32) -> SDL_Window*
    {
        static int winNumber = 0;
        ++winNumber;
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
    std::function<Uint32(SDL_Window*)>                                  mockSDL_GetWindowID         = [](SDL_Window* w) -> Uint32 {return reinterpret_cast<std::uintptr_t>(w);};
    std::function<int(SDL_Renderer*, int, int)>                         mockSDL_RenderDrawPoint     = [](SDL_Renderer*, int, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Point const*, int)>            mockSDL_RenderDrawPoints    = [](SDL_Renderer*, SDL_Point const*, int){return 0;};
    std::function<int(SDL_Renderer*, int, int, int, int)>               mockSDL_RenderDrawLine      = [](SDL_Renderer*, int, int, int, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Point const*, int)>            mockSDL_RenderDrawLines     = [](SDL_Renderer*, SDL_Point const*, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*)>                  mockSDL_RenderFillRect      = [](SDL_Renderer*, SDL_Rect const*){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*)>                  mockSDL_RenderDrawRect      = [](SDL_Renderer*, SDL_Rect const*){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*, int)>             mockSDL_RenderFillRects     = [](SDL_Renderer*, SDL_Rect const*, int){return 0;};
    std::function<int(SDL_Renderer*, SDL_Rect const*, int)>             mockSDL_RenderDrawRects     = [](SDL_Renderer*, SDL_Rect const*, int){return 0;};

    std::function<Uint8*(int*)>                                         mockSDL_GetKeyboardState    = [](int* key){static Uint8 keys[255];(*key)=255;return keys;};
    std::function<void(void)>                                           mockSDL_StartTextInput      = [](){};
    std::function<void(void)>                                           mockSDL_StopTextInput       = [](){};

    std::function<SDL_Texture*(SDL_Renderer*, SDL_Surface*)>            mockSDL_CreateTextureFromSurface    = [](SDL_Renderer*, SDL_Surface*) -> SDL_Texture* {return reinterpret_cast<SDL_Texture*>(1);};
    std::function<void(SDL_Texture*)>                                   mockSDL_DestroyTexture              = [](SDL_Texture*){};

    std::function<SDL_Surface*(TTF_Font*, char const*, SDL_Color)>      mockTTF_RenderText_Solid            = [](TTF_Font*, char const*, SDL_Color) -> SDL_Surface* {return reinterpret_cast<SDL_Surface*>(1);};
    std::function<SDL_Surface*(TTF_Font*, char const*, SDL_Color)>      mockTTF_RenderUTF8_Solid            = [](TTF_Font*, char const*, SDL_Color) -> SDL_Surface* {return reinterpret_cast<SDL_Surface*>(1);};
    std::function<void(SDL_Surface*)>                                   mockSDL_FreeSurface                 = [](SDL_Surface*){};

    std::function<int(SDL_Texture*, Uint32*, int*, int*, int*)>         mockSDL_QueryTexture                = [](SDL_Texture*, Uint32*, int*, int*, int*){return 0;};
    std::function<int(SDL_Renderer*, SDL_Texture*, SDL_Rect const*, SDL_Rect const*)>   mockSDL_RenderCopy  = [](SDL_Renderer*, SDL_Texture*, SDL_Rect const*, SDL_Rect const*){return 0;};

    std::function<int()>                                                mockTTF_Init                = []()                  {return 0;};
    std::function<void()>                                               mockTTF_Quit                = []()                  {};
    std::function<TTF_Font*(char const*, int)>                          mockTTF_OpenFont            = [](char const*, int)  {return reinterpret_cast<TTF_Font*>(1);};
    std::function<void(TTF_Font*)>                                      mockTTF_CloseFont           = [](TTF_Font*)         {};

    std::function<int(int)>                                             mockIMG_Init                = [](int x)                                 {return x;};
    std::function<void()>                                               mockIMG_Quit                = []()                                      {};
    std::function<SDL_Surface*(SDL_RWops*, int)>                        mockIMG_Load_RW             = [](SDL_RWops*, int)                       {return reinterpret_cast<SDL_Surface*>(1);};
    std::function<int(SDL_Surface*, SDL_RWops*, int)>                   mockIMG_SavePNG_RW          = [](SDL_Surface*, SDL_RWops*, int)         {return 0;};
    std::function<int(SDL_Surface*, SDL_RWops*, int, int)>              mockIMG_SaveJPG_RW          = [](SDL_Surface*, SDL_RWops*, int, int)    {return 0;};
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

    MOCK_MEM_DECL(SDL_GetKeyboardState);
    MOCK_MEM_DECL(SDL_StartTextInput);
    MOCK_MEM_DECL(SDL_StopTextInput);

    MOCK_MEM_DECL(SDL_CreateTextureFromSurface);
    MOCK_MEM_DECL(SDL_DestroyTexture);

    MOCK_MEM_DECL(TTF_RenderText_Solid);
    MOCK_MEM_DECL(TTF_RenderUTF8_Solid);
    MOCK_MEM_DECL(SDL_FreeSurface);

    MOCK_MEM_DECL(SDL_QueryTexture);
    MOCK_MEM_DECL(SDL_RenderCopy);

    MOCK_MEM_DECL(TTF_Init);
    MOCK_MEM_DECL(TTF_Quit);
    MOCK_MEM_DECL(TTF_OpenFont);
    MOCK_MEM_DECL(TTF_CloseFont);

    MOCK_MEM_DECL(IMG_Init);
    MOCK_MEM_DECL(IMG_Quit);
    MOCK_MEM_DECL(IMG_Load_RW);
    MOCK_MEM_DECL(IMG_SavePNG_RW);
    MOCK_MEM_DECL(IMG_SaveJPG_RW);
 
    public:
        MockSDL(MocksSDLActions& action)
            : MOCK_MEM_INIT(SDL_Init,               [&action](Uint32 f)                                             {++action.count[countSDL_Init];return action.mockSDL_Init(f);})
            , MOCK_MEM_INIT(SDL_Quit,               [&action]()                                                     {++action.count[countSDL_Quit];return action.mockSDL_Quit();})
            , MOCK_MEM_INIT(SDL_InitSubSystem,      [&action](Uint32 f)                                             {++action.count[countSDL_InitSubSystem];return action.mockSDL_InitSubSystem(f);})
            , MOCK_MEM_INIT(SDL_QuitSubSystem,      [&action](Uint32 f)                                             {++action.count[countSDL_QuitSubSystem];return action.mockSDL_QuitSubSystem(f);})
            , MOCK_MEM_INIT(SDL_CreateWindow,       [&action](char const* t, int x, int y, int w, int h, Uint32 f)  {++action.count[countSDL_CreateWindow];return action.mockSDL_CreateWindow(t, x, y, w, h, f);})
            , MOCK_MEM_INIT(SDL_DestroyWindow,      [&action](SDL_Window* w)                                        {++action.count[countSDL_DestroyWindow];return action.mockSDL_DestroyWindow(w);})
            , MOCK_MEM_INIT(SDL_CreateRenderer,     [&action](SDL_Window* w, int i, Uint32 f)                       {++action.count[countSDL_CreateRenderer];return action.mockSDL_CreateRenderer(w, i, f);})
            , MOCK_MEM_INIT(SDL_DestroyRenderer,    [&action](SDL_Renderer* r)                                      {++action.count[countSDL_DestroyRenderer];return action.mockSDL_DestroyRenderer(r);})
            , MOCK_MEM_INIT(SDL_PollEvent,          [&action](SDL_Event* e)                                         {++action.count[countSDL_PollEvent];return action.mockSDL_PollEvent(e);})
            , MOCK_MEM_INIT(SDL_SetHint,            [&action](char const* n, char const* v)                         {++action.count[countSDL_SetHint];return action.mockSDL_SetHint(n, v);})
            , MOCK_MEM_INIT(SDL_SetRenderDrawColor, [&action](SDL_Renderer* re, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {++action.count[countSDL_SetRenderDrawColor];return action.mockSDL_SetRenderDrawColor(re, r, g, b, a);})
            , MOCK_MEM_INIT(SDL_RenderClear,        [&action](SDL_Renderer* r)                                      {++action.count[countSDL_RenderClear];return action.mockSDL_RenderClear(r);})
            , MOCK_MEM_INIT(SDL_RenderPresent,      [&action](SDL_Renderer* r)                                      {++action.count[countSDL_RenderPresent];return action.mockSDL_RenderPresent(r);})
            , MOCK_MEM_INIT(SDL_GetWindowID,        [&action](SDL_Window* w)                                        {++action.count[countSDL_GetWindowID];return action.mockSDL_GetWindowID(w);})
            , MOCK_MEM_INIT(SDL_RenderDrawPoint,    [&action](SDL_Renderer* r, int x, int y)                        {++action.count[countSDL_RenderDrawPoint];return action.mockSDL_RenderDrawPoint(r, x, y);})
            , MOCK_MEM_INIT(SDL_RenderDrawPoints,   [&action](SDL_Renderer* r, SDL_Point const* p, int c)           {++action.count[countSDL_RenderDrawPoints];return action.mockSDL_RenderDrawPoints(r, p, c);})
            , MOCK_MEM_INIT(SDL_RenderDrawLine,     [&action](SDL_Renderer* r, int x1, int y1, int x2, int y2)      {++action.count[countSDL_RenderDrawLine];return action.mockSDL_RenderDrawLine(r, x1, x2, y1, y2);})
            , MOCK_MEM_INIT(SDL_RenderDrawLines,    [&action](SDL_Renderer* r, SDL_Point const* p, int c)           {++action.count[countSDL_RenderDrawLines];return action.mockSDL_RenderDrawLines(r, p, c);})
            , MOCK_MEM_INIT(SDL_RenderFillRect,     [&action](SDL_Renderer* r, SDL_Rect const* rp)                  {++action.count[countSDL_RenderFillRect];return action.mockSDL_RenderFillRect(r, rp);})
            , MOCK_MEM_INIT(SDL_RenderDrawRect,     [&action](SDL_Renderer* r, SDL_Rect const* rp)                  {++action.count[countSDL_RenderDrawRect];return action.mockSDL_RenderDrawRect(r, rp);})
            , MOCK_MEM_INIT(SDL_RenderFillRects,    [&action](SDL_Renderer* r, SDL_Rect const* rp, int c)           {++action.count[countSDL_RenderFillRects];return action.mockSDL_RenderFillRects(r, rp, c);})
            , MOCK_MEM_INIT(SDL_RenderDrawRects,    [&action](SDL_Renderer* r, SDL_Rect const* rp, int c)           {++action.count[countSDL_RenderDrawRects];return action.mockSDL_RenderDrawRects(r, rp, c);})

            , MOCK_MEM_INIT(SDL_GetKeyboardState,   [&action](int* count)                                           {++action.count[countSDL_GetKeyboardState];return action.mockSDL_GetKeyboardState(count);})
            , MOCK_MEM_INIT(SDL_StartTextInput,     [&action]()                                                     {++action.count[countSDL_StartTextInput];return action.mockSDL_StartTextInput();})
            , MOCK_MEM_INIT(SDL_StopTextInput,      [&action]()                                                     {++action.count[countSDL_StopTextInput];return action.mockSDL_StopTextInput();})

            , MOCK_MEM_INIT(SDL_CreateTextureFromSurface,   [&action](SDL_Renderer* r, SDL_Surface* s)              {++action.count[countSDL_CreateTextureFromSurface];return action.mockSDL_CreateTextureFromSurface(r, s);})
            , MOCK_MEM_INIT(SDL_DestroyTexture,     [&action](SDL_Texture* t)                                       {++action.count[countSDL_DestroyTexture];return action.mockSDL_DestroyTexture(t);})

            , MOCK_MEM_INIT(TTF_RenderText_Solid,   [&action](TTF_Font* f, char const* m, SDL_Color c)              {++action.count[countTTF_RenderText_Solid];return action.mockTTF_RenderText_Solid(f, m, c);})
            , MOCK_MEM_INIT(TTF_RenderUTF8_Solid,   [&action](TTF_Font* f, char const* m, SDL_Color c)              {++action.count[countTTF_RenderUTF8_Solid];return action.mockTTF_RenderUTF8_Solid(f, m, c);})
            , MOCK_MEM_INIT(SDL_FreeSurface,        [&action](SDL_Surface* s)                                       {++action.count[countSDL_FreeSurface];return action.mockSDL_FreeSurface(s);})

            , MOCK_MEM_INIT(SDL_QueryTexture,       [&action](SDL_Texture* t, Uint32* f, int* a, int* w, int* h)    {++action.count[countSDL_QueryTexture];return action.mockSDL_QueryTexture(t, f, a, w, h);})
            , MOCK_MEM_INIT(SDL_RenderCopy,         [&action](SDL_Renderer* r, SDL_Texture* t, SDL_Rect const* d, SDL_Rect const* s)    {++action.count[countSDL_RenderCopy];return action.mockSDL_RenderCopy(r, t, d, s);})

            , MOCK_MEM_INIT(TTF_Init,               [&action]()                                                     {++action.count[countTTF_Init];return action.mockTTF_Init();})
            , MOCK_MEM_INIT(TTF_Quit,               [&action]()                                                     {++action.count[countTTF_Quit];return action.mockTTF_Quit();})
            , MOCK_MEM_INIT(TTF_OpenFont,           [&action](char const* n, int p)                                 {++action.count[countTTF_OpenFont];return action.mockTTF_OpenFont(n, p);})
            , MOCK_MEM_INIT(TTF_CloseFont,          [&action](TTF_Font* f)                                          {++action.count[countTTF_CloseFont];return action.mockTTF_CloseFont(f);})

            , MOCK_MEM_INIT(IMG_Init,               [&action](int flag)                                             {++action.count[countIMG_Init];return action.mockIMG_Init(flag);})
            , MOCK_MEM_INIT(IMG_Quit,               [&action]()                                                     {++action.count[countIMG_Quit];return action.mockIMG_Quit();})
            , MOCK_MEM_INIT(IMG_Load_RW,            [&action](SDL_RWops* w,int f)                                   {++action.count[countIMG_Load_RW];return action.mockIMG_Load_RW(w, f);})
            , MOCK_MEM_INIT(IMG_SavePNG_RW,         [&action](SDL_Surface* s,SDL_RWops* w, int f)                   {++action.count[countIMG_SavePNG_RW];return action.mockIMG_SavePNG_RW(s, w, f);})
            , MOCK_MEM_INIT(IMG_SaveJPG_RW,         [&action](SDL_Surface* s,SDL_RWops* w, int f, int q)            {++action.count[countIMG_SaveJPG_RW];return action.mockIMG_SaveJPG_RW(s, w, f, q);})

        {}

};

#endif
