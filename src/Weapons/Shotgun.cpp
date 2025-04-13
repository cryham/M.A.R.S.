/* Shotgun.cpp

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

#include "Weapons/Shotgun.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Shotgun::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    const float r = parent_->radius();
    const int u = 1, v = 31;
    glBegin(GL_QUADS);
        glTexCoord2f(u*0.125f,     v*0.03125f);    glVertex2f(0,     r* 0.3f);
        glTexCoord2f(u*0.125f,    (v+1)*0.03125f); glVertex2f(0,     r*-0.3f);
        glTexCoord2f((u+1)*0.125f,(v+1)*0.03125f); glVertex2f(r*3.f, r*-0.3f);
        glTexCoord2f((u+1)*0.125f, v*0.03125f);    glVertex2f(r*3.f, r* 0.3f);
    glEnd();
}

void Shotgun::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 1.0)
    {
        timer_ = time;
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        
        for (int i=0; i < 25; ++i)
            particles::spawn(particles::pAmmoShotgun, parent_->location() + dir*parent_->radius(),
                dir, parent_->velocity(), Color3f(), parent_->getOwner());
        
        parent_->velocity() -= dir * 200.f;  // knock back
        sound::playSound(sound::Pump, parent_->location());
    }
}


float Shotgun::maxDistance() const
{
    return 300.f;
}

float Shotgun::minDistance() const
{
    return 0.f;
}

float Shotgun::maxAngle() const
{
    return 20.f;
}
