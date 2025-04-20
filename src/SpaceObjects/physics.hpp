#pragma once

#include "System/Vector2f.hpp"

#include <vector>
#include <list>


const int
    MOBILES   = 1,
    STATICS   = 2,
    PARTICLES = 4;

class SpaceObject;
class MobileSpaceObject;
class Player;


namespace physics 
{
    void     overlap        (MobileSpaceObject* source, int with);
    void     collide        (MobileSpaceObject* source, int with);
    Vector2f attract        (MobileSpaceObject* attracted);
    void     borders        (MobileSpaceObject* source);
    void     causeShockWave (Player* damageSource, Vector2f const& location, float strength, float radius, float damage);

    void addMobileObject    (MobileSpaceObject* source);
    void removeMobileObject (MobileSpaceObject* source);
    void addStaticObject    (SpaceObject* source);
    void removeStaticObject (SpaceObject* source);
    void addGravitySource   (SpaceObject* source);

    std::vector<SpaceObject*> const& getGravitySources();

    void clear();
}
