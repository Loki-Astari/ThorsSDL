#include "View.h"
#include "Sprite.h"
#include "ThorsUI/Application.h"
#include "ThorsUI/Window.h"
#include "ThorsUI/Surface.h"
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

        virtual void draw(ThorsAnvil::UI::DrawContext& /*drawContext*/)
        {
        }
        virtual bool doUpdateState()
        {
            return true;
        }
};
int main()
{
    ThorsAnvil::UI::Application             application(ThorsAnvil::UI::Video, ThorsAnvil::UI::Images);
    ThorsAnvil::UI::Window                  window("Test Widgets", {100, 100, 200, 200});
    ThorsAnvil::Graphics::View              graphicsView(window);
    ImageSprite                             sprite(graphicsView);

    window.updateView(0, true);
    application.eventLoop(1000);
}
