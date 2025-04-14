/* ships.cpp

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

#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/Turret.hpp"

#include <vector>


namespace ships  // and turrets
{
    namespace
    {
        std::vector<Ship*> shipList_;
        std::vector<Turret*> turretList_;
    }

    void addShip(Vector2f const& location, float rotation, Player* owner)
    {
        shipList_.push_back(new Ship(location, rotation, owner));
    }

    void addTurret(Vector2f const& location, float rotation, Player* owner)
    {
        turretList_.push_back(new Turret(location, rotation, owner));
    }

    void update()
    {
        for (auto& it : shipList_)
            it->update();
        for (auto& it : turretList_)
            it->update();
    }

    void draw()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));

        for (const auto& it : shipList_)
            it->drawWeapon();
        for (const auto& it : turretList_)
            it->drawWeapon();

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

        for (const auto& it : shipList_)
            it->draw();
        for (const auto& it : turretList_)
            it->draw();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::vector<Ship*> const& getShips()
    {
        return shipList_;
    }

    std::vector<Turret*> const& getTurrets()
    {
        return turretList_;
    }

    void clear()
    {
        for (auto& it : shipList_)
            delete it;
        shipList_.clear();
        
        for (auto& it : turretList_)
            delete it;
        turretList_.clear();
    }
}
