#include "Sprite.h"
#include "GraphicView.h"

using namespace ThorsAnvil::Graphics;


Sprite::Sprite(GraphicView& parent, int millisecondUpdateTime)
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

void Sprite::updateState()
{
    UI::TimePoint   now =  std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= updatePeriod)
    {
        if (doUpdateState())
        {
            lastUpdate = now;
        }
    }
}

void Sprite::draw(UI::DrawContext& /*drawContext*/)
{}

bool Sprite::doUpdateState()
{
    return true;
}

void Sprite::reset()
{}
