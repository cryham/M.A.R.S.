/* AmmoGauss.cpp

Copyright (c) 2025 Crystal Hammer

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
#include "TrailEffects/Trail.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "defines.hpp"


std::list<AmmoGauss*> AmmoGauss::activeParticles_;


AmmoGauss::AmmoGauss(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoGauss>(spaceObjects::oAmmoGauss, location, 1.f, 0.001f, 1.0f)
{
    setDamageSource(damageSource);
    velocity_ = direction * 12100.f;
    location_ += velocity_*timer::frameTime()*1.2f;

    // trail_ = trailEffects::attach(this, 0.05, 1.f, 4.f, Color3f(0.3f, 0.1f, 0.2f), false);
}

AmmoGauss::~AmmoGauss()
{
    // trailEffects::detach(this);
}


void AmmoGauss::update()
{
    float time = timer::frameTime();

    for (int i=0; i < steps_; ++i)
    {
        physics::collide(this, STATICS | MOBILES);
        location_ += velocity_ * time;
        borders();
        lifeTime_ += time;

        // if (i != steps_-1)
        //     trail_->update();
    }
}

//  draw
void AmmoGauss::draw() const
{
    glColor4f(0.8f, 1.f, 1.f, 1.f);

    Vector2f dir(velocity_ * 0.0025f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    side *= 0.5f;

    const Vector2f topLeft(location_ + dir + side),
        topRight(location_ + dir - side),
        btmL(location_ - 1*dir + side),
        btmR(location_ - 1*dir - side);

    const float u = 0, v = 2.5f;
    uv8(u,   v);       glVertex2f(topLeft.x_, topLeft.y_);
    uv8(u,   v+0.5f);  glVertex2f(btmL.x_, btmL.y_);
    uv8(u+3, v+0.5f);  glVertex2f(btmR.x_, btmR.y_);
    uv8(u+3, v);       glVertex2f(topRight.x_, topRight.y_);
}


void AmmoGauss::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity - velocity_).length() / 10.f;

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
    }
    // if (with->type() != spaceObjects::oAmmoFlubba &&
        // with->type() != spaceObjects::oAmmoH2OMG &&
        // with->type() != spaceObjects::oMiniAmmoFlubba)
        killMe();
}
