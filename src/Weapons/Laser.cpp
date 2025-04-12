/* Laser.cpp

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

#include "Weapons/Laser.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Laser::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0, 1.2, 0.2, 1.f); //alpha);

    const float r = parent_->radius();
    const int posX = 0;
    const int posY = 31;
    glBegin(GL_QUADS);
        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(0,     r* 0.2f);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(0,     r*-0.2f);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(r*9.f, r*-0.2f);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(r*9.f, r* 0.2f);
    glEnd();
}

void Laser::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.01)
        return;
    timer_ = time;
    float angleRad = parent_->rotation()*M_PI / 180;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoLaser, parent_->location() + dir*parent_->radius(), dir,
        parent_->velocity(), Color3f(), parent_->getOwner());
    
    //sound::playSound(sound::Check, parent_->location());
}


float Laser::maxDistance() const
{
    return 1500.f;
}

float Laser::minDistance() const
{
    return 0.f;
}

float Laser::maxAngle() const
{
    return 5.f;
}
