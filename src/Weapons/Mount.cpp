#include "Weapons/Mount.hpp"
#include "Players/Player.hpp"


Mount::Mount(float rotation, Player* owner)
    // ,weaponChangeTime_(0.f)
    :owner_(owner)
    // ,radius(1.f)
    ,rotation_(rotation)
    ,rotateSpeed_(1.f)
    // ,left_(0), right_(0)
{
}

Player* Mount::getOwner() const
{
    return owner_;
}

float Mount::rotation() const
{
    return rotation_;
}
