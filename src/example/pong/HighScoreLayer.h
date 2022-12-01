#ifndef THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_LAYER
#define THORSANVIL_UI_EXAMPLE_PONG_HIGH_SCORE_LAYER

#include "ThorsSDL/Application.h"
#include "ThorsSDL/Window.h"
#include "ThorsSDL/Sprite.h"
#include "ThorsSDL/Pen.h"
#include <vector>

namespace ThorsAnvil::UI::Example::Pong
{

namespace UI = ThorsAnvil::UI;

class HighScoreLayer
{
    struct HighScore
    {
        std::string     name;
        std::string     date;
        int             score;
    };
    class HighScoreTable: public UI::Sprite
    {
        Application&                application;
        Window&                     window;
        UI::TextPen                 pen;
        UI::Rect                    rect;
        std::vector<HighScore>      scores{ {"Martin",  "1/1/2023",  150},
                                            {"Loki",    "2/1/2023",  140},
                                            {"Thor",    "3/1/2023",  130},
                                            {"Odin",    "4/1/2023",  120},
                                            {"Iron Man","5/1/2023",  110}
                                          };
        public:
            HighScoreTable(Application& application, Window& parent, std::size_t layer, UI::Rect const& rect);
            virtual void doDraw(DrawContext& context) override;
            virtual bool doUpdateState() override;
    };

    HighScoreTable       highScoreTable;

    public:
        HighScoreLayer(UI::Application& application, UI::Window& window, std::size_t layer, UI::Rect const& rect)
            : highScoreTable(application, window, layer, rect)
        {}
};

}

#endif
