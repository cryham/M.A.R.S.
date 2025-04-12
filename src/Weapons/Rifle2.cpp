/* Rifle2.cpp

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

#include "Weapons/Rifle2.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Rifle2::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 0.4, 0.7, alpha);

    const float r = parent_->radius();
    const int posX = 0;
    const int posY = 31;
    glBegin(GL_QUADS);
        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(0,     r* 0.2f);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(0,     r*-0.2f);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(r*6.f, r*-0.2f);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(r*6.f, r* 0.2f);
    glEnd();
}

void Rifle2::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.1)
        return;
    timer_ = time;
    
    float angleRad = parent_->rotation()*M_PI / 180;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoRifle2, parent_->location() + dir*parent_->radius(), dir,
        parent_->velocity(), Color3f(), parent_->getOwner());
    
    sound::playSound(sound::Sniper, parent_->location());
}


float Rifle2::maxDistance() const
{
    return FLT_MAX;
}

float Rifle2::minDistance() const
{
    return 0.f;
}

float Rifle2::maxAngle() const
{
    return 5.f;
}
