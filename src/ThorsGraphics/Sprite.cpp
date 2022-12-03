#include "Sprite.h"
#include "Window.h"

using namespace ThorsAnvil::UI;


Sprite::Sprite(Window& parent, std::size_t layer, int millisecondUpdateTime)
    : parent(parent)
    , lastUpdate{}
    , updatePeriod(millisecondUpdateTime)
{
    parent.addSprite(*this, layer);
}

Sprite::~Sprite()
{
    parent.remSprite(*this);
}

void Sprite::updateState()
{
    TimePoint   now =  std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= updatePeriod)
    {
        if (doUpdateState())
        {
            lastUpdate = now;
        }
    }
}
