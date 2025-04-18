#include "Items/PUFuel.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"


void PUFuel::draw() const
{
    if (!collected_)
        PowerUp::draw();
}

void PUFuel::refreshLifeTime()
{
    lifeTime_ = totalLifeTime_;
    for (auto& it : ships_)
        it->refuel(it->owner_, 100);
    
    // direction is abused for texture coords
    particles::spawnMultiple(5, particles::pPowerUpCollect, location_, Vector2f(3,1));
}
