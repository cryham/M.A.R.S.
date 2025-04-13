/* AmmoGrenades.cpp

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

#include "Particles/AmmoGrenades.hpp"

#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoGrenades*> AmmoGrenades::activeParticles_;


AmmoGrenades::AmmoGrenades(
    Vector2f const& location, Vector2f const& direction,
    Vector2f const& velocity, Color3f const& color,
    Player* damageSource)
    :Particle<AmmoGrenades>(spaceObjects::oAmmoGrenades, location, 8.f, 1.0f, randomizer::random(1.0f, 1.2f))
{
    setDamageSource(damageSource);
    velocity_ = velocity + direction * 900;
    location_ += velocity_*timer::frameTime()*1.2f;

    radius_ = randomizer::random(6.f, 7.f);

    color_ = Color3f(randomizer::random(0.5f, 0.6f), randomizer::random(0.56f, 0.67f), randomizer::random(0.6f, 0.7f));
}

void AmmoGrenades::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS | MOBILES); // | PARTICLES);
    Vector2f acceleration = physics::attract(this)*0.8f;

    if (lifeTime_ > totalLifeTime_-0.3f)
        radius_ = -400.0 * pow(lifeTime_+0.2-totalLifeTime_, 2) + 12;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time - 2.5f*velocity_*time;
    borders();

    lifeTime_ += time;
    if (lifeTime_ > totalLifeTime_)
    {
        particles::spawnMultiple(3, particles::pSpark, location_, Vector2f(), Vector2f(), color_);
        sound::playSound(sound::BlubCollide, location_);

        int cnt = randomizer::random(21, 32);
        for (int i=0; i < cnt; ++i)
        {
            Vector2f dir = Vector2f::randDir();
            particles::ParticleType type = 
                rand()%10 > 5 ? particles::pAmmoMinigun :
                // rand()%10 > 5 ? particles::pSpark :
                rand()%10 > 5 ? particles::pAmmoShotgun2 : particles::pAmmoShotgun;
            // particles::spawn(type, location_,
            // particles::spawn(particles::pAmmoMinigun, location_,
            // particles::spawn(particles::pAmmoShotgun, location_,
            particles::spawn(particles::pAmmoShotgun2, location_,
                dir, dir * randomizer::random(1.f, 2.f), Color3f(), damageSource_);
        }
        // postFX::onExplosion();
        // setDamageSource(parent_);
        // physics::causeShockWave(damageSource(), location_, 150.f, 300.f, 3.f);
        particles::spawn(particles::pShockWave, location_);
        physics::causeShockWave(damageSource(), location_, 150.f, 400.f, 6.f);
        killMe();
    }
}

//  draw
void AmmoGrenades::draw() const
{
    color_.gl4f(1.f);
    const int posX = 4;
    const int posY = 0;
    uv8(posX, posY);      glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(posX, posY+1);    glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(posX+1, posY+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(posX+1, posY);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoGrenades::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    if (!isDead() &&
        with->type() != spaceObjects::oAmmoGrenades /*&&
        with->type() != spaceObjects::oMiniAmmoGrenades*/)
    {
        physics::causeShockWave(damageSource(), location_, 350.f, 100.f, 0.f);
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
}

void AmmoGrenades::shockWave(Vector2f const& location, float strength, float radius)
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
