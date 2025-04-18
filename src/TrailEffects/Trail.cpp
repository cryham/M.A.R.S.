#include "TrailEffects/Trail.hpp"
#include "SpaceObjects/SpaceObject.hpp"


Trail::Trail(SpaceObject* target):
    target_(target)
{   }

void Trail::detach()
{
    target_ = nullptr;
}

SpaceObject* Trail::target() const
{
    return target_;
}
