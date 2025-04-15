/* Mud.cpp

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

#include "Particles/Mud.hpp"

#include "System/timer.hpp"
#include "System/randomizer.hpp"


std::list<Mud*> Mud::activeParticles_;


Mud::Mud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Mud>(spaceObjects::oMud, location, 1.f, 0.f, randomizer::random(0.6f, 0.8f))
    ,color_(color)
{
    Vector2f distortion(Vector2f::randDirLen());
    velocity_ = direction + distortion*150;
}

void Mud::update()
{
    // update Color
    color_.v(-1.0/totalLifeTime_*lifeTime_+1);

    float time = timer::frameTime();
    Vector2f acceleration = physics::attract(this);

    location_ += velocity_*time + acceleration*time*time*5;
    velocity_ += acceleration*time*5 + velocity_*-2*time;
    // borders();

    lifeTime_ += time;
}

void Mud::draw() const
{
    color_.gl4f();
    const int u = 0, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
