/* AmmoMinigun.cpp

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

#include "Particles/AmmoMinigun.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "System/randomizer.hpp"


std::list<AmmoMinigun*> AmmoMinigun::activeParticles_;


AmmoMinigun::AmmoMinigun(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource):
         Particle<AmmoMinigun>(spaceObjects::oAmmoMinigun, location, 1.5f, 0.05f, randomizer::random(1.2f, 1.5f)),
         color_(1.f, randomizer::random(0.7f, 1.f), 0.3f)
{
    setDamageSource(damageSource);
    velocity_ = direction*1900.f *randomizer::random(0.98f, 1.02f) + Vector2f::randDirLen()*40.f;
    location_ += velocity_*timer::frameTime()*1.2f;

    trail_ = randomizer::random(0.f, 1.f) < 0.3f;
    if (trail_)
        trailEffects::attach(this, 0.01f, 0.1f, 1.5f, Color3f(color_.r()*0.8f, color_.g()*0.6f, color_.g()*0.3f), false);
}

AmmoMinigun::~AmmoMinigun()
{
    if (trail_)
        trailEffects::detach(this);
}

void AmmoMinigun::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS | MOBILES);
    Vector2f acceleration = physics::attract(this)*15;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time - velocity_*time;
    borders();

    // color_.v(-1.f / totalLifeTime_ * lifeTime_+1.f);

    lifeTime_ += time;
}

void AmmoMinigun::draw() const
{
    color_.gl4f(1.f - 0.5f * lifeTime_ / totalLifeTime_);
    const int posX = 0;
    const int posY = 1;
    glTexCoord2f(posX*0.125f,     posY*0.125f);     glVertex2f(location_.x_-radius_, location_.y_-radius_);
    glTexCoord2f(posX*0.125f,     (posY+1)*0.125f); glVertex2f(location_.x_-radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, (posY+1)*0.125f); glVertex2f(location_.x_+radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, posY*0.125f);     glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoMinigun::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity - velocity_).length();

    if (randomizer::random(0.f, 1.f) < 0.3f)  // otherwise ricochet
    {   killMe();
        if (strength > 50.f)
        {
            switch (with->type())
            {
                case spaceObjects::oShip:
                    sound::playSound(sound::Particle, location, (strength-50)/3);
                    break;

                case spaceObjects::oBall:
                    sound::playSound(sound::Particle, location, (strength-50)/3);
                    break;

                case spaceObjects::oPlanet: case spaceObjects::oHome:
                    sound::playSound(sound::Particle, location, (strength-50)/3);
                    break;

                case spaceObjects::oSun:
                    sound::playSound(sound::Particle, location, (strength-50)/3);
                    break;

                default:;
            }
        }
    }
}
