/* Gauss.cpp

Copyright (c) 2025 Crystal Hammer

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

#include "Weapons/Gauss.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Gauss::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.2, 0.6, 1.0, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.2f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.2f);
        uv8w(u+1, v+1); glVertex2f(r*6.f, r*-0.2f);
        uv8w(u+1, v);   glVertex2f(r*6.f, r* 0.2f);
    glEnd();
    glColor4f(1.0, 1.0, 0.3, 0.5);  // aim dir
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,      r* 0.8f);
        uv8w(u, v+1);   glVertex2f(0,      r*-0.8f);
        uv8w(u+1, v+1); glVertex2f(r*91.f, r*-0.8f);
        uv8w(u+1, v);   glVertex2f(r*91.f, r* 0.8f);
    glEnd();
}

void Gauss::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.3)
        return;
    timer_ = time;
    float angleRad = parent_->rotation()*M_PI / 180;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoGauss, parent_->getLocation() + dir*parent_->getRadius(),
        dir, parent_->getVelocity(), Color3f(), parent_->getOwner());
    
    sound::playSound(sound::Sniper, parent_->getLocation());
}


float Gauss::maxDistance() const
{
    return FLT_MAX;
}

float Gauss::minDistance() const
{
    return 0.f;
}

float Gauss::maxAngle() const
{
    return 5.f;
}
