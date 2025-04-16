/* AmmoLightning.cpp

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

#include "Particles/AmmoLightning.hpp"

#include "SpaceObjects/physics.hpp"
#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoLightning*> AmmoLightning::activeParticles_;


AmmoLightning::AmmoLightning(
    Vector2f const& location, Vector2f const& direction,
    Vector2f const& velocity, Color3f const& color,
    Player* damageSource)
    :Particle<AmmoLightning>(spaceObjects::oAmmoLightning, location, 2.f, 0.001f, randomizer::random(0.4f, 1.5f))
    ,spawnTime_(0.f)
{
    cloud_ = true;
    setDamageSource(damageSource);
    Vector2f side(direction.y_, -direction.x_);

    velocity_ = velocity + direction * randomizer::random(1500.f, 2400.f) +
        200.f * side * randomizer::random(-1.f, 1.f) +
        Vector2f::randDir() * randomizer::random(0.f, 100.f);
    acceleration_ = -randomizer::random(300.f, 600.f);

    location_ += velocity_*timer::frameTime()*1.2f;
    radius_ = randomizer::random(6.f, 8.f) * 8.f;
    size_ = radius_;

    color_ = Color3f(randomizer::random(0.5f, 0.9f), randomizer::random(0.6f, 0.8f), 1.f);
}


void AmmoLightning::update()
{
    float time = timer::frameTime();

    physics::overlap(this, MOBILES | STATICS);

    radius_ = size_ + 40.f * std::min(3.f, 3.f * lifeTime_);

    location_ += velocity_*time;
    Vector2f const dir(velocity_.normalize());
    velocity_ += acceleration_ * dir * time;
    borders();

    lifeTime_ += time;
    spawnTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        killMe();
    }
    else if (lifeTime_ < 2)
    {
        if (spawnTime_ > 0.1f)
        {   spawnTime_ = 0.f;

            Vector2f dir = Vector2f::randDir();
            float len = randomizer::random(2.f, radius_ * 0.3f);

            particles::spawnMultiple(0.5f,
                             particles::pSpark,    location_ + dir * len, dir, dir * len * 5.2f, color_);
            particles::spawn(particles::pElectric, location_ + dir * len, dir, dir * len * 0.9f, color_);
        }
    }
}

//  draw
void AmmoLightning::draw() const
{
    float a = 0.1f + 0.2f * std::min(1.f, 3.2f * lifeTime_ / totalLifeTime_);
    a *= 0.7f * (totalLifeTime_ - lifeTime_) / totalLifeTime_;

    Vector2f dir(velocity_.normalize() * 1.f * radius_);
    Vector2f side(dir.y_, -dir.x_);
    side *= 1.2f;
    const Vector2f
        topL(location_ + side + dir), topL2(location_ + side*0.38f + dir*1.3f), topL3(location_ + side*1.1f + dir*1.51f),
        topR(location_ + side - dir), topR2(location_ + side*0.36f - dir*1.6f), topR3(location_ + side*0.9f - dir*1.57f),
        btmL(location_ - side + dir), btmL2(location_ - side*0.47f + dir*2.4f), btmL3(location_ - side*1.3f + dir*1.53f),
        btmR(location_ - side - dir), btmR2(location_ - side*0.45f - dir*2.7f), btmR3(location_ - side*0.7f - dir*1.51f);

    int v = 2, u;
    color_.gl4f(a * 0.9f + 0.1f * sinf(0.5f + lifeTime_ * 23.f));
    u = 8 + ((int)(lifeTime_ * 26.f) % 4) * 2;
    uv8(u,   v+4);  glVertex2f(topL.x_, topL.y_);
    uv8(u+2, v+4);  glVertex2f(btmL.x_, btmL.y_);
    uv8(u+2, v);    glVertex2f(btmR.x_, btmR.y_);
    uv8(u,   v);    glVertex2f(topR.x_, topR.y_);

    color_.brightened().gl4f(a * 2.5f + 0.07f * cosf(lifeTime_ * 53.f));
    u = 8 + ((int)(lifeTime_ * 36.f) % 4) * 2;
    uv8(u,   v);    glVertex2f(topL2.x_, topL2.y_);
    uv8(u+2, v);    glVertex2f(btmL2.x_, btmL2.y_);
    uv8(u+2, v+4);  glVertex2f(btmR2.x_, btmR2.y_);
    uv8(u,   v+4);  glVertex2f(topR2.x_, topR2.y_);

    color_.gl4f(a * 1.2f + 0.05f * sinf(lifeTime_ * 67.f));
    u = 8 + ((int)(lifeTime_ * 56.f) % 4) * 2;
    uv8(u,   v);    glVertex2f(topL3.x_, topL3.y_);
    uv8(u+2, v);    glVertex2f(btmL3.x_, btmL3.y_);
    uv8(u+2, v+4);  glVertex2f(btmR3.x_, btmR3.y_);
    uv8(u,   v+4);  glVertex2f(topR3.x_, topR3.y_);
}


void AmmoLightning::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    return;
    if (!isDead() &&
        with->type() != spaceObjects::oAmmoLightning /*&&
        with->type() != spaceObjects::oMiniAmmoLightning*/)
    {
        physics::causeShockWave(damageSource(), location_, 350.f, 100.f, 0.f);
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
}
