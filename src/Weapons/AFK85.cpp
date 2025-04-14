/* AFK85.cpp

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

#include "Weapons/AFK85.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "System/Color3f.hpp"
#include "System/Vector2f.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


AFK85::AFK85(Mount* parent)
    :Weapon(weapons::wAFK85, parent, sf::String("AFK-85"))
{
    if (parent_ && parent_->getOwner())
        color_ = parent_->getOwner()->color();
    else
        color_ = Color3f(0.6,0.6,1.0);
}

void AFK85::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color_.gl4f(alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 28;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0, r*0.95f);
        uv8w(u, v+1);   glVertex2f(0, r*0.45f);
        uv8w(u+1, v+1); glVertex2f(r*1.5f, r*0.45f);
        uv8w(u+1, v);   glVertex2f(r*1.5f, r*0.95f);

        uv8w(u, v);     glVertex2f(0, -1.f*r*0.95f);
        uv8w(u, v+1);   glVertex2f(0, -1.f*r*0.45f);
        uv8w(u+1, v+1); glVertex2f(r*1.5f, -1.f*r*0.45f);
        uv8w(u+1, v);   glVertex2f(r*1.5f, -1.f*r*0.95f);
    glEnd();
}

void AFK85::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.05)
    {   timer_ = time;

        const float r = parent_->getRadius();
        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        Vector2f pos = parent_->getLocation(), vel = parent_->getVelocity();

        particles::spawn(particles::pAmmoAFK85, Vector2f(pos.x_ + dir.x_*r*0.7 - dir.y_*r*0.7,
            pos.y_ +  dir.x_*r*0.5 + dir.y_*r*0.5), dir,
            vel, Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(pos.x_ + dir.x_*r*0.7 - dir.y_*r*0.7,
            pos.y_ +  dir.x_*r*0.5 + dir.y_*r*0.5), dir,
            vel, Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(pos.x_ + dir.x_*r*0.9 + dir.y_*r*0.9,
            pos.y_ - dir.x_*r*0.7 + dir.y_*r*0.7), dir,
            vel, Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(pos.x_ + dir.x_*r*0.9 + dir.y_*r*0.9,
            pos.y_ - dir.x_*r*0.7 + dir.y_*r*0.7), dir,
            vel, Color3f(), parent_->getOwner());

        sound::playSound(sound::Laser, pos);
    }
}


float AFK85::maxDistance() const
{
    return FLT_MAX;
}

float AFK85::minDistance() const
{
    return 0.f;
}

float AFK85::maxAngle() const
{
    return 10.f;
}
