/* AmmoCloud.cpp

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

#include "Particles/AmmoCloud.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoCloud*> AmmoCloud::activeParticles_;


AmmoCloud::AmmoCloud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoCloud>(spaceObjects::oAmmoCloud, location, randomizer::random(19.f, 25.f), 0.01f, randomizer::random(2.f, 4.f))
{
    setDamageSource(damageSource);
    velocity_ = velocity + direction*500;
    acceleration_ = 600.0f;
    location_ += velocity_*timer::frameTime()*1.2f;

    radius_ = randomizer::random(17.f, 21.f) * 4.f;

    color_ = Color3f(randomizer::random(0.5f, 0.7f), randomizer::random(0.5f, 0.8f), randomizer::random(0.8f, 0.9f));
}

AmmoCloud::~AmmoCloud()
{
}

void AmmoCloud::update()
{
    float time = timer::frameTime();

    physics::overlap(this, MOBILES);
    // Vector2f acceleration; // = physics::attract(this)*0.8f;  //..add?

    location_ += velocity_*time;  // + acceleration*time*time;
    // velocity_ += acceleration*time + 0.1f*velocity_*time;
    Vector2f const faceDirection(velocity_.normalize());
    velocity_ += acceleration_ * faceDirection * time;
    radius_ = 84.f + 120.4f * lifeTime_ / totalLifeTime_;
    borders();

    lifeTime_ += time;
    spawnTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        // particles::spawnMultiple(2, particles::pMud, location_, Vector2f(), Vector2f(), color_);
        // int rand = randomizer::random(8, 20);
        // sound::playSound(sound::BlubCollide, location_);
        killMe();
    }else
    if (lifeTime_ < 2)
    {
        if (spawnTime_ > 0.1f) //+ 0.1f * lifeTime_)
        {   spawnTime_ = 0.f;

            Vector2f dir = Vector2f::randDir();
            float len = randomizer::random(10.f, radius_);
            particles::spawnMultiple(1,
                particles::pMud, location_ + dir * len, dir, dir * len * 0.9f, color_);
        }
    }
}

void AmmoCloud::draw() const
{
    color_.gl4f(0.5f - 0.4f * lifeTime_ / totalLifeTime_);
    // const int posX = 3, posY = 0;
    const int posX = 0, posY = 0;
    uv8(posX, posY);      glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(posX, posY+1);    glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(posX+1, posY+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(posX+1, posY);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoCloud::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    // no collision
}

void AmmoCloud::shockWave(Vector2f const& location, float strength, float radius)
{
    for (auto& it : activeParticles_)
    {
        Vector2f direction(it->location_ - location);
        float distance = direction.length();
        if (distance < radius && direction != Vector2f())
        {
            float intensity = radius-distance;
            direction = direction.normalize();
            direction *= intensity;
            it->velocity_ += direction;
        }
    }
}
