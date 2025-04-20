#pragma once

#include "System/Color3f.hpp"

class SpaceObject;
class Trail;


namespace trailEffects 
{
    void update();

    void draw();

    Trail* attach(SpaceObject* target, float timeStep, float duration, float width, Color3f const& color, bool persistant);

    void detach(SpaceObject* target);

    int  count();

    void clear();
}
