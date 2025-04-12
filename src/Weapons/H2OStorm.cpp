/* H2OStorm.cpp

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

#include "Weapons/H2OStorm.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void H2OStorm::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.7f, 0.8f, 1.f);

    const float r = parent_->radius();
    const int posX = 0;
    const int posY = 29;
    glBegin(GL_QUADS);
        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(0,     r* 0.8f);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(0,     r*-0.8f);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(r*4.f, r*-0.8f);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(r*4.f, r* 0.8f);
    glEnd();
}

void H2OStorm::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.02f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        particles::spawn(particles::pAmmoH2OStorm, parent_->location() + dir*parent_->radius()*1.5, dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoH2OStorm, parent_->location() + dir*parent_->radius(), dir,
            parent_->velocity(), Color3f(), parent_->getOwner());
        sound::playSound(sound::BlubPop, parent_->location());

        // parent_->velocity() -= faceDirection*20.f;
    }
}


float H2OStorm::maxDistance() const
{
    return FLT_MAX;
}

float H2OStorm::minDistance() const
{
    return 0.f;
}

float H2OStorm::maxAngle() const
{
    return 20.f;
}
