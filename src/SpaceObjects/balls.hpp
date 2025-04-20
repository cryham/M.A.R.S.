#pragma once

#include "System/Vector2f.hpp"

class Ball;


namespace balls
{
    void addBall(int id, float radius, Vector2f const& location);

    void update();
    void draw();

    Ball* getBall();

    void clear();
}
