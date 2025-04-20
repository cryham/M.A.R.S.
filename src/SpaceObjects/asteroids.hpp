#pragma once

#include "System/Vector2f.hpp"
#include "SpaceObjects/Ball.hpp"


namespace asteroids
{
    void addAsteroid(float radius, Vector2f const& location, int type);

    void update();
    void draw();

    void clear();
}
