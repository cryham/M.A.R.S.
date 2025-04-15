/* ships.hpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

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
