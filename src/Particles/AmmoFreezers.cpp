/* AmmoFreezers.cpp

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

#include "Particles/AmmoFreezers.hpp"

#include "SpaceObjects/physics.hpp"
#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoFreezers*> AmmoFreezers::activeParticles_;


AmmoFreezers::AmmoFreezers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoFreezers>(spaceObjects::oAmmoFreezers, location,
        randomizer::random(9.f, 15.f), 0.01f, randomizer::random(12.f, 15.f))
{
    cloud_ = true;
    setDamageSource(damageSource);
    spawnTime_ = 0.f;
    Vector2f side(direction.y_, -direction.x_);

    velocity_ = velocity + direction * 900 + 100.f * side * randomizer::random(-1.f, 1.f);
    location_ += velocity_ * timer::frameTime()*1.2f;

    radius_ = randomizer::random(7.f, 12.f) * 4.f;

    color_ = Color3f(randomizer::random(0.2f, 0.4f), randomizer::random(0.6f, 0.8f), 1.f);

    // trailEffects::attach(this, 0.02, 0.1f, radius_ * 2.5f, Color3f(0.14f, randomizer::random(0.21f, 0.35f), 0.35f), false);
}

AmmoFreezers::~AmmoFreezers()
{
    // trailEffects::detach(this);
}

//  update
void AmmoFreezers::update()
{
    float time = timer::frameTime();

    physics::overlap(this, STATICS | MOBILES);
    Vector2f acceleration = physics::attract(this) * 0.8f;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time - 0.1f*velocity_*time;
    radius_ -= 1.2f * time * lifeTime_ / totalLifeTime_;
    borders();

    lifeTime_ += time;
    spawnTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        // particles::spawnMultiple(1, particles::pMud, location_, Vector2f(), Vector2f(), color_);
        // int rand = randomizer::random(8, 20);
        // sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
    else if (lifeTime_ < 2)
    {
        if (spawnTime_ > 0.04f)
        {   spawnTime_ = 0.f;

            Vector2f dir = Vector2f::randDir();
            float len = randomizer::random(3.f, radius_ * 0.3f);
            particles::spawnMultiple(1,
                particles::pMud, location_ + dir * len, dir, dir * len * 0.9f, color_);
        }
    }
}

void AmmoFreezers::draw() const
{
    color_.gl4f(0.6f);
    const int posX = 10, posY = 0;
    uv8(posX, posY);      glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(posX,   posY+3);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(posX+3, posY+3);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(posX+3, posY);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoFreezers::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    if (!isDead() && with->type() != spaceObjects::oAmmoFreezers /*&& with->type() != spaceObjects::oMiniAmmoFreezers*/)
    {
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
}
