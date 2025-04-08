/* AmmoFlamer2.cpp

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

#include "Particles/AmmoFlamer2.hpp"

#include "System/timer.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoFlamer2*> AmmoFlamer2::activeParticles_;


AmmoFlamer2::AmmoFlamer2(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoFlamer2>(spaceObjects::oAmmoFlamer2, location, 1.f, 0.f, randomizer::random(0.4f, 0.5f))
{
    setDamageSource(damageSource);
    Vector2f distortion(Vector2f::randDirLen()*3.f);
    location_ = location + direction*randomizer::random(0.f, 20.f) + 
        10.f * Vector2f(randomizer::random(-1.f, 1.f), randomizer::random(-1.f, 1.f));
    velocity_ = velocity + direction*900.f + distortion*17.f;

    color_.h(50.f);
    color_.v(0.8f);
    color_.s(0.3f);
}

void AmmoFlamer2::update()
{
    float time = timer::frameTime();
    physics::collide(this, STATICS);
    // update Color
    color_.h((-1.0f/totalLifeTime_*lifeTime_+1.f)*60.f);
    color_.v(-0.8f/totalLifeTime_*lifeTime_+0.8f);
    color_.s(lifeTime_*10.f + 0.3f);

    // update Size
    radius_ = lifeTime_*40 + 15;

    location_ += velocity_*time;
    velocity_ += velocity_*(-0.14f)*time;
    velocity_ += (0.2f + time*0.02f ) * Vector2f(randomizer::random(-1.f, 1.f), randomizer::random(-1.f, 1.f));
    borders();

    lifeTime_ += time;

    // check for collisions with ships
    const auto& shipsList = ships::getShips();
    for (const auto& it : shipsList)
        if ((location_ - it->location()).lengthSquare() < std::pow(radius_ + it->radius(), 2) && it->collidable())
            it->onCollision(this, location_, velocity_, velocity_);

    // check for collisions with ball
    Ball* ball = balls::getBall();
    if (ball)
        if ((location_ - ball->location()).lengthSquare() < std::pow(radius_ + ball->radius(), 2))
            ball->onCollision(this, location_, velocity_, velocity_);
}

//  draw
void AmmoFlamer2::draw() const
{
    color_.gl4f(0.15f);
    const int posX = 0;
    const int posY = 0;
    glTexCoord2f(posX*0.125f,     posY*0.125f);     glVertex2f(location_.x_-radius_, location_.y_-radius_);
    glTexCoord2f(posX*0.125f,     (posY+1)*0.125f); glVertex2f(location_.x_-radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, (posY+1)*0.125f); glVertex2f(location_.x_+radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, posY*0.125f);     glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoFlamer2::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    killMe();
}
