/* HeatBurner.cpp

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

#include "Particles/HeatBurner.hpp"

#include "System/timer.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/Ship.hpp"
#include "System/randomizer.hpp"


std::list<HeatBurner*> HeatBurner::activeParticles_;


HeatBurner::HeatBurner(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<HeatBurner>(spaceObjects::oHeatBurner, location, 1.f, 0.f, randomizer::random(0.4f, 0.5f))
{
    Vector2f distortion(Vector2f::randDirLen()*3.f);
    location_ = location + direction*randomizer::random(0.f, 20.f);
    velocity_ = velocity + direction*700.f + distortion*70.f;
}

void HeatBurner::update()
{
    float time = timer::frameTime();

    // update Size
    radius_ = lifeTime_*50 + 2;

    location_ += velocity_*time;
    velocity_ += velocity_*(-2.f)*time;
    borders();

    lifeTime_ += time;
}

void HeatBurner::draw() const
{
    glColor4f(1.f, 1.f, 1.f, 1.f - lifeTime_/totalLifeTime_);
    const int u = 3, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+2);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+2, v+2);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+2, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
