#include "Items/PUHealth.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"


void PUHealth::draw() const
{
    if (!collected_)
        PowerUp::draw();
}

void PUHealth::refreshLifeTime()
{
    lifeTime_ = totalLifeTime_;
    for (auto& it : ships_)
        it->heal(it->owner_, 100);
    
    // direction is abused for texture coords
    particles::spawnMultiple(5, particles::pPowerUpCollect, location_, Vector2f(0,1));
}
