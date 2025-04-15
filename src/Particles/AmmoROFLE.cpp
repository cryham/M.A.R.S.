/* AmmoROFLE.cpp

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

#include "Particles/AmmoROFLE.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "defines.hpp"


std::list<AmmoROFLE*> AmmoROFLE::activeParticles_;


AmmoROFLE::AmmoROFLE(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoROFLE>(spaceObjects::oAmmoROFLE, location, 1.f, 3.0f, 3.0f)
{
    setDamageSource(damageSource);
    velocity_ = direction*1300.f;
    location_ += velocity_*timer::frameTime()*1.2f;

    trailEffects::attach(this, 0.05, 1.f, 4.f, Color3f(1.f, 0.2f, 0.f), false);
}

AmmoROFLE::~AmmoROFLE()
{
    trailEffects::detach(this);
}


void AmmoROFLE::update()
{
    float time = timer::frameTime()*0.5f;

    for (int i=0; i<2; ++i)
    {
        physics::collide(this, STATICS | MOBILES);
        location_ += velocity_*time;
        borders();
        lifeTime_ += time;
    }

    if (location_.x_ < -100 || location_.x_ > settings::iMapXsize + 100 ||
        location_.y_ < -100 || location_.y_ > settings::iMapYsize + 100)
        killMe();
}

void AmmoROFLE::draw() const
{
    glColor4f(1.f, 1.f, 1.f, 1.f);

    Vector2f dir(velocity_*0.025f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    side *= 0.05f;

    const Vector2f
        topL(location_ + dir + side),
        topR(location_ + dir - side),
        btmL(location_ - 3*dir + side),
        btmR(location_ - 3*dir - side);

    const float u = 0, v = 2.5f;
    uv8(u,   v);       glVertex2f(topL.x_, topL.y_);
    uv8(u,   v+0.5f);  glVertex2f(btmL.x_, btmL.y_);
    uv8(u+3, v+0.5f);  glVertex2f(btmR.x_, btmR.y_);
    uv8(u+3, v);       glVertex2f(topR.x_, topR.y_);
}

void AmmoROFLE::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity-velocity_).length();

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

    if (with->type() != spaceObjects::oAmmoFlubba &&
        with->type() != spaceObjects::oAmmoH2OMG &&
        with->type() != spaceObjects::oMiniAmmoFlubba)
        killMe();
}
