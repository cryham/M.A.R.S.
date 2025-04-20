#pragma once

#include "System/Vector2f.hpp"
#include <vector>

class Player;
class Ship;
class Turret;


namespace ships  // and turrets
{
    float GetAngle(float x, float y);  // radians

    void addShip(Vector2f const& location, float rotation, Player* owner);
    void addTurret(Vector2f const& location, float rotation, Player* owner);
    void createTurrets();

    void update();
    void draw();
    void drawTurrets();

    std::vector<Ship*> const& getShips();
    std::vector<Turret*> const& getTurrets();

    void clear();
}
