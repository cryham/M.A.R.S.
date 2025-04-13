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

#include <SFML/Graphics.hpp>
#include <cfloat>


void AFK85::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    parent_->getOwner()->color().gl4f(alpha);

    const float r = parent_->radius();
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

        const float r = parent_->radius();
        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        particles::spawn(particles::pAmmoAFK85, Vector2f(parent_->location().x_ + dir.x_*r*0.7 - dir.y_*r*0.7,
            parent_->location().y_ +  dir.x_*r*0.5 + dir.y_*r*0.5), dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(parent_->location().x_ + dir.x_*r*0.7 - dir.y_*r*0.7,
            parent_->location().y_ +  dir.x_*r*0.5 + dir.y_*r*0.5), dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(parent_->location().x_ + dir.x_*r*0.9 + dir.y_*r*0.9,
            parent_->location().y_ - dir.x_*r*0.7 + dir.y_*r*0.7), dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoAFK85, Vector2f(parent_->location().x_ + dir.x_*r*0.9 + dir.y_*r*0.9,
            parent_->location().y_ - dir.x_*r*0.7 + dir.y_*r*0.7), dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        sound::playSound(sound::Laser, parent_->location());
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
