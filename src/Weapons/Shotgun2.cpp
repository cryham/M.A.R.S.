/* Shotgun2.cpp

Copyright (c) 2025 Crystal Hammer
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

#include "Weapons/Shotgun2.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Shotgun2::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.5f, 1.0f, alpha);

    const float r = parent_->radius();
    const int posX = 0;
    const int posY = 30;
    glBegin(GL_QUADS);
        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(0,      r* 0.8f);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(0,      r*-0.8f);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(r*2.5f, r*-0.8f);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(r*2.5f, r* 0.8f);
    glEnd();
}

void Shotgun2::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.2)
    {   timer_ = time;
        
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        for (int i=0; i < 75; ++i)
            particles::spawn(particles::pAmmoShotgun2, parent_->location() + dir*parent_->radius(),
                dir, parent_->velocity(), Color3f(), parent_->getOwner());

        parent_->velocity() -= dir * 50.f;
        sound::playSound(sound::Pump, parent_->location());
    }
}


float Shotgun2::maxDistance() const
{
    return 300.f;
}

float Shotgun2::minDistance() const
{
    return 0.f;
}

float Shotgun2::maxAngle() const
{
    return 20.f;
}
