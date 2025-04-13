/* RasterZone.cpp

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

#include "Zones/RasterZone.hpp"
#include "SpaceObjects/SpaceObject.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "System/randomizer.hpp"

#include <cfloat>


RasterZone::RasterZone(Vector2f const& btmL, Vector2f const& topRight):
    btmL_(btmL),
    topR_(topRight),
    covered_(false)
{   }

bool RasterZone::isInside(SpaceObject const& toBeChecked) const
{
    return toBeChecked.location().x_ > btmL_.x_ &&
           toBeChecked.location().y_ > btmL_.y_ &&
           toBeChecked.location().x_ < topR_.x_ &&
           toBeChecked.location().y_ < topR_.y_;
}

void RasterZone::update()
{
    covered_ = false;
    std::vector<Ship*> const& ships = ships::getShips();
    for (const auto& it : ships)
        if (isInside(*it))
        {
            covered_ = true;
            break;
        }
}

//  draw
void RasterZone::draw() const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBegin(GL_QUADS);
        if (!covered_)
            glColor4f (0.f, 0.7f, 0.f, 0.1f);
        else
            glColor4f (6.f, 0.2f, 0.f, 0.1f);
        glVertex2f(btmL_.x_, btmL_.y_);
        glVertex2f(btmL_.x_, topR_.y_);
        glVertex2f(topR_.x_, topR_.y_);
        glVertex2f(topR_.x_, btmL_.y_);
    glEnd();
    
    glLineWidth(2.f);
    glBegin(GL_LINE_LOOP);
        glColor4f(0.5f, 0.5f, 0.5f, 0.3f);
        glVertex2f(btmL_.x_, btmL_.y_);
        glVertex2f(btmL_.x_, topR_.y_);
        glVertex2f(topR_.x_, topR_.y_);
        glVertex2f(topR_.x_, btmL_.y_);
    glEnd();
}

Vector2f RasterZone::getRandomPoint() const
{
    Vector2f randomPoint;
    for (int i=0; i < 100; ++i)
    {
        randomPoint = Vector2f(
            randomizer::random(btmL_.x_, topR_.x_),
            randomizer::random(btmL_.y_, topR_.y_));
        bool fits = true;
        for (const auto& it : spaceObjects::getObjects())
        {
            if ((randomPoint - it->location()).lengthSquare() < std::pow(it->radius() + 50, 2))
                fits = false;
        }
        if (fits)
            break;
    }
    return randomPoint;
}

bool RasterZone::covered() const
{
    return covered_;
}
