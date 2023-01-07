#include "View.h"
#include "Sprite.h"
#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include "ThorsUI/Surface.h"
#include "ThorsUI/Texture.h"
#include <fstream>

class ImageSprite: public ThorsAnvil::Graphics::Sprite
{
    ThorsAnvil::UI::Surface     image;
    public:
        ImageSprite(ThorsAnvil::Graphics::View& parent )
            : Sprite(parent, 20)
        {
            std::ifstream   file("test/data/Apple.jpg", std::ios::binary);
            file >> image;
            if (!file) {
                std::cerr << "Failed to load Apple\n" << "Error: " << SDL_GetError() << "\n";
            }
        }

        virtual void draw(ThorsAnvil::UI::DrawContext& drawContext)
        {
            ThorsAnvil::UI::Texture     texture{drawContext, image};
            ThorsAnvil::UI::Sz          textSize{texture.size()};
            double factor = 800.0/textSize.y;
            texture.draw({10,10, static_cast<int>(textSize.x * factor), static_cast<int>(textSize.y * factor)}, {0, 0, textSize.x, textSize.y});
        }
        virtual bool doUpdateState()
        {
            return true;
        }
};
int main()
{
    ThorsAnvil::UI::Application             application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Images);
    ThorsAnvil::UI::Window                  window("Test Widgets", {100, 100, 1500, 1500});
    ThorsAnvil::Graphics::View              graphicsView(window);
    ImageSprite                             sprite(graphicsView);

    window.updateView(0, true);
    application.eventLoop(1000);
}
