#pragma once

#include "System/Vector2f.hpp"
#include "SpaceObjects/Ball.hpp"


namespace balls 
{
    void addBall(float radius, Vector2f const& location = Vector2f(0, 0));

    void update();
    void draw();

    Ball* getBall();

    void clear();
}
