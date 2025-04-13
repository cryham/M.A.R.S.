/* Insta.cpp

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

#include "Weapons/Insta.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Insta::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    parent_->getOwner()->team()->color().brightened().gl4f(alpha);

    const float r = parent_->radius();
    const int u = 2, v = 31;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,      r* 0.2f);
        uv8w(u, v+1);   glVertex2f(0,      r*-0.2f);
        uv8w(u+1, v+1); glVertex2f(r*4.5f, r*-0.2f);
        uv8w(u+1, v);   glVertex2f(r*4.5f, r* 0.2f);
    glEnd();
}

void Insta::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 3.0)
    {   timer_ = time;
    
        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        Color3f tmp = parent_->getOwner()->team()->color().brightened();
        
        particles::spawn(particles::pAmmoInsta, parent_->location() + dir*parent_->radius(), dir,
            parent_->velocity(), tmp, parent_->getOwner());
        
        sound::playSound(sound::Sniper, parent_->location());
    }
}


float Insta::maxDistance() const
{
    return FLT_MAX;
}

float Insta::minDistance() const
{
    return 500.f;
}

float Insta::maxAngle() const
{
    return 30.f;
}
