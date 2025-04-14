/* BlackHole.cpp

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

#include "SpaceObjects/BlackHole.hpp"
#include "System/Color3f.hpp"
#include "System/timer.hpp"
#include "System/randomizer.hpp"

#include <cmath>


BlackHole::BlackHole(Vector2f const& location, float radius)
    :SpaceObject(spaceObjects::oBlackHole, location, radius, radius * randomizer::random(110, 170))  // 130
    ,rotation_(0)
{
    physics::addGravitySource(this);
    float b = std::min(1.f, std::max(0.f, radius / 300.f ));
    color_ = Color3f(1.f - randomizer::random(0.f, 0.1f) - 0.5f * b,
                     1.f - randomizer::random(0.f, 0.3f) - 0.7f * b,
                     1.f - randomizer::random(0.f, 0.2f) - 0.4f * b);
}

void BlackHole::update()
{
    rotation_ = fmod(rotation_ += 10*timer::frameTime(), 360);
}

void BlackHole::draw() const
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0);
    glRotatef(rotation_, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Hole1));

    color_.gl4f(0.2f);
    float r = radius_*1.8f;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-r, -r);
        glTexCoord2i(0, 1); glVertex2f(-r,  r);
        glTexCoord2i(1, 1); glVertex2f( r,  r);
        glTexCoord2i(1, 0); glVertex2f( r, -r);
    glEnd();
    
    color_.gl4f(0.6f);
    glRotatef(rotation_*-2, 0, 0, 1);
    r = radius_*1.3f;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-r, -r);
        glTexCoord2i(0, 1); glVertex2f(-r,  r);
        glTexCoord2i(1, 1); glVertex2f( r,  r);
        glTexCoord2i(1, 0); glVertex2f( r, -r);
    glEnd();
    
    color_.gl4f(1.f);
    glRotatef(rotation_*4, 0, 0, 1);
    r = radius_;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-r, -r);
        glTexCoord2i(0, 1); glVertex2f(-r,  r);
        glTexCoord2i(1, 1); glVertex2f( r,  r);
        glTexCoord2i(1, 0); glVertex2f( r, -r);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
