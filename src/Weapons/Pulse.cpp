/* Pulse.cpp

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

#include "Weapons/Pulse.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>


void Pulse::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(1.f, 0.5f, 0.8f);

    const float r = parent_->radius();
    const int u = 0, v = 29;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 1.6f);
        uv8w(u, v+1);   glVertex2f(0,     r*-1.6f);
        uv8w(u+1, v+1); glVertex2f(r*2.f, r*-1.6f);
        uv8w(u+1, v);   glVertex2f(r*2.f, r* 1.6f);
    glEnd();
}

void Pulse::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.2f) return;
    timer_ = time;
    float angleRad = parent_->rotation()*M_PI / 180.f;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoPulse, parent_->location() + dir*parent_->radius(), dir,
        parent_->velocity(), Color3f(), parent_->getOwner());

    parent_->velocity() -= dir * 10.f;
    sound::playSound(sound::Blub, parent_->location());
}


float Pulse::maxDistance() const
{
    return 300.f;
}

float Pulse::minDistance() const
{
    return 20.f;
}

float Pulse::maxAngle() const
{
    return 70.f;
}
