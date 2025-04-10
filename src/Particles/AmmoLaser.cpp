/* AmmoLaser.cpp

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

#include "Particles/AmmoLaser.hpp"

#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/Trail.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "defines.hpp"


std::list<AmmoLaser*> AmmoLaser::activeParticles_;


AmmoLaser::AmmoLaser(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource):
         Particle<AmmoLaser>(spaceObjects::oAmmoLaser, location, 1.f, 0.0001f, 3.0f)
{
    for (int i=0; i < steps_; ++i)
        pos_[i] = location;
    setDamageSource(damageSource);
    velocity_ = direction * 610.f;
    location_ += velocity_ * timer::frameTime() * 1.1f;

    trail_ = trailEffects::attach(this, 0.01f, 0.02f, 22.f, 0.6f * Color3f(0.4f, 0.2f, 0.1f), true);
}

AmmoLaser::~AmmoLaser()
{
    trailEffects::detach(this);
}


void AmmoLaser::update()
{
    float time = timer::frameTime();
    // float time = timer::frameTime()/steps_;  // slow-

    for (int i=0; i < steps_; ++i)
    {
        pos_[i] = location_;
        physics::collide(this, STATICS | MOBILES);
        location_ += velocity_ * time;
        borders();
        lifeTime_ += time;

        if (i != steps_-1)
            trail_->update();
    }

    // if (location_.x_ < -100 || location_.x_ > settings::C_MapXsize + 100 ||
    //     location_.y_ < -100 || location_.y_ > settings::C_MapYsize + 100)
    //     killMe();
}

//  draw
void AmmoLaser::draw() const
{
    /**
    glColor4f(1.0f, 0.6f, 0.2f, 1.f);

    Vector2f direction(velocity_ * 0.001f);
    direction.normalize();
    Vector2f side(-direction.y_, direction.x_);
    side *= 30.f;

    // const int posX = 0;
    // const float posY = 2.5f;
    // const int posX = 0;
    // const int posY = 31;
    const int posX = 0;
    const int posY = 0;
    
    Vector2f p = pos_[0];
    for (int i=1; i <= steps_; ++i)
    {
        const Vector2f pp = i == steps_ ? location_ : pos_[i];
        const Vector2f
            topLeft (pp + side),
            topRight(pp - side),
            bottomLeft (p + side),
            bottomRight(p - side);
        p = pp;

        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(topLeft.x_, topLeft.y_);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(bottomLeft.x_, bottomLeft.y_);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(bottomRight.x_, bottomRight.y_);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(topRight.x_, topRight.y_);
    }
    /*
    float time = 0.001f; //timer::frameTime();
    for (int i=0; i < steps_; ++i)
    {
        Vector2f pos = location_ + direction * i / steps_;
        const Vector2f
            topLeft (pos + side),
            topRight(pos - side),
            bottomLeft (p + side),
            bottomRight(p - side);
        p = pos;

        glTexCoord2f(posX*0.125f,     posY*0.03125f);    glVertex2f(topLeft.x_, topLeft.y_);
        glTexCoord2f(posX*0.125f,    (posY+1)*0.03125f); glVertex2f(bottomLeft.x_, bottomLeft.y_);
        glTexCoord2f((posX+1)*0.125f,(posY+1)*0.03125f); glVertex2f(bottomRight.x_, bottomRight.y_);
        glTexCoord2f((posX+1)*0.125f, posY*0.03125f);    glVertex2f(topRight.x_, topRight.y_);
    }*/
}


void AmmoLaser::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    /*float strength = (velocity-velocity_).length() / 10.f;

    if (strength > 50.f)
    {
        switch (with->type())
        {
            case spaceObjects::oShip:
                sound::playSound(sound::SniperShipCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oBall:
                sound::playSound(sound::SniperShipCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oPlanet: case spaceObjects::oHome:
                sound::playSound(sound::SniperPlanetCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oSun:
                sound::playSound(sound::SniperPlanetCollide, location, (strength-50)/3);
                break;

            default:;
        }
    }*/
    // if (with->type() != spaceObjects::oAmmoFlubba && with->type() != spaceObjects::oAmmoH2OMG && with->type() != spaceObjects::oMiniAmmoFlubba)
    //     killMe();
}
