/* AmmoPulse.cpp

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

#include "Particles/AmmoPulse.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoPulse*> AmmoPulse::activeParticles_;


AmmoPulse::AmmoPulse(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoPulse>(spaceObjects::oAmmoPulse, location, randomizer::random(19.f, 25.f), 0.01f, randomizer::random(2.f, 4.f))
{
    cloud_ = true;
    setDamageSource(damageSource);
    velocity_ = velocity + direction * 1100;
    acceleration_ = 800.0f;
    location_ += velocity_*timer::frameTime()*1.2f;

    radius_ = randomizer::random(17.f, 21.f) * 4.f;

    color_ = Color3f(randomizer::random(0.6f, 1.f), randomizer::random(0.2f, 0.6f), randomizer::random(0.5f, 0.8f));
    trailEffects::attach(this, 0.005, 0.12f, 160.f, color_ * 0.5f, false);
}

AmmoPulse::~AmmoPulse()
{
    trailEffects::detach(this);
}

void AmmoPulse::update()
{
    float time = timer::frameTime();

    physics::overlap(this, MOBILES | STATICS);

    location_ += velocity_*time;
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
                particles::pSpark, location_ + dir * len, dir, dir * len * 0.9f, color_);
        }
    }
}

void AmmoPulse::draw() const
{
    color_.gl4f(0.9f - 0.4f * lifeTime_ / totalLifeTime_);
    const int u = 0, v = 12;

    Vector2f dir(velocity_.normalize() * 20.f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    const Vector2f
        topL(location_ + 3*side + dir*1),
        topR(location_ + 3*side - dir*3),
        btmL(location_ - 3*side + dir*1),
        btmR(location_ - 3*side - dir*3);

    uv8(u,   v);    glVertex2f(topL.x_, topL.y_);
    uv8(u+4, v);    glVertex2f(btmL.x_, btmL.y_);
    uv8(u+4, v+2);  glVertex2f(btmR.x_, btmR.y_);
    uv8(u,   v+2);  glVertex2f(topR.x_, topR.y_);
}

void AmmoPulse::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    // no collision
}

void AmmoPulse::shockWave(Vector2f const& location, float strength, float radius)
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
