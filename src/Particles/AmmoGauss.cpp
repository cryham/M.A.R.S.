/* AmmoGauss.cpp

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

#include "Particles/AmmoGauss.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "defines.hpp"


std::list<AmmoGauss*> AmmoGauss::activeParticles_;


AmmoGauss::AmmoGauss(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource):
         Particle<AmmoGauss>(spaceObjects::oAmmoGauss, location, 1.f, 0.001f, 3.0f)
{
    setDamageSource(damageSource);
    velocity_ = direction * 12100.f;
    location_ += velocity_*timer::frameTime()*1.2f;

    // trailEffects::attach(this, 0.05, 1.f, 4.f, Color3f(0.3f, 0.1f, 0.2f), false);
}

AmmoGauss::~AmmoGauss()
{
    // trailEffects::detach(this);
}


void AmmoGauss::update()
{
    float time = timer::frameTime()*0.5f;

    for (int i=0; i < 12; ++i)
    {
        physics::collide(this, STATICS | MOBILES);
        location_ += velocity_*time;
        borders();
        lifeTime_ += time;
    }

    if (location_.x_ < -100 || location_.x_ > settings::C_MapXsize + 100 ||
        location_.y_ < -100 || location_.y_ > settings::C_MapYsize + 100)
        killMe();
}

//  draw
void AmmoGauss::draw() const
{
    glColor4f(0.5f, 1.f, 1.f, 1.f);

    Vector2f direction(velocity_*0.025f);
    Vector2f normDirection(direction.y_, -1.f*direction.x_);
    normDirection *= 0.05f;

    const Vector2f topLeft(location_ + direction + normDirection),
        topRight(location_ + direction - normDirection),
        bottomLeft(location_ - 1*direction + normDirection),
        bottomRight(location_ - 1*direction - normDirection);

    const int posX = 0;
    const float posY = 2.5f;
    uv8(posX, posY);         glVertex2f(topLeft.x_, topLeft.y_);
    uv8(posX, posY+0.5f);    glVertex2f(bottomLeft.x_, bottomLeft.y_);
    uv8(posX+3, posY+0.5f);  glVertex2f(bottomRight.x_, bottomRight.y_);
    uv8(posX+3, posY);       glVertex2f(topRight.x_, topRight.y_);
}

void AmmoGauss::onCollision(SpaceObject* with, Vector2f const& location,
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
    if (with->type() != spaceObjects::oAmmoFlubba && with->type() != spaceObjects::oAmmoH2OMG && with->type() != spaceObjects::oMiniAmmoFlubba)
        killMe();
}
