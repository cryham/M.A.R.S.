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
#include "SpaceObjects/spaceObjects.hpp"
#include "SpaceObjects/Home.hpp"
#include "SpaceObjects/Planet.hpp"
#include "System/randomizer.hpp"
#include "System/settings.hpp"

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

    //  draw  ----
    void draw()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));

        for (const auto& it : shipList_)
            it->drawWeapon();

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

        for (const auto& it : shipList_)
            it->draw();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawTurrets()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));

        for (const auto& it : turretList_)
            it->drawWeapon();

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

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


    //  angle
    float GetAngle(float x, float y)
    {
        if (x == 0.f && y == 0.f)
            return 0.f;

        if (y == 0.f)
            return (x < 0.f) ? M_PI : 0.f;
        else
            return (y < 0.f) ? atan2f(-y, x) : (2.f * M_PI - atan2f(y, x));
    }


    //  turrets  ----
    void createTurrets()
    {
        int cnt = settings::iTurretsOnHome;
        for (auto& p : spaceObjects::getHomes())
            for (int i=0; i < cnt; ++i)
            {
                auto dir = Vector2f::randDir();
                auto ang = GetAngle(dir.x_, dir.y_);
                float r = p->radius() * randomizer::random(0.9f, 1.f);

                Vector2f pos = p->location();
                addTurret(pos, ang, NULL);
            }
        
        cnt = settings::iTurretsOnPlanet;
        for (auto& p : spaceObjects::getPlanets())
            for (int i=0; i < cnt; ++i)
            {
                auto dir = Vector2f::randDir();
                auto ang = GetAngle(dir.x_, dir.y_);
                float r = p->radius() * randomizer::random(1.f, 1.1f);  //-

                Vector2f pos = p->location() + dir * r;
                addTurret(pos, ang, NULL);
            }
    }
}
