#include "Sprite.h"
#include "View.h"

using namespace ThorsAnvil::Graphics;


Sprite::Sprite(View& parent, int millisecondUpdateTime)
    : parent(parent)
    , lastUpdate{}
    , updatePeriod(millisecondUpdateTime)
{
    parent.addSprite(*this);
}

Sprite::~Sprite()
{
    parent.remSprite(*this);
}

bool Sprite::updateState()
{
    bool dirty = false;
    UI::TimePoint   now =  std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= updatePeriod)
    {
        if (doUpdateState())
        {
            lastUpdate = now;
            dirty = true;
        }
    }
    return dirty;
}

void Sprite::draw(UI::DrawContext& /*drawContext*/)
{}

bool Sprite::doUpdateState()
{
    // By default we will always draw.
    //
    // If you want your sprite to be efficient then
    // override this and only set true when the state of your
    // sprite changes.
    return true;
}

void Sprite::reset()
{}
