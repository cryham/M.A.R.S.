/* AmmoPlasma.cpp

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

#include "Particles/AmmoPlasma.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoPlasma*> AmmoPlasma::activeParticles_;


AmmoPlasma::AmmoPlasma(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource)
    :Particle<AmmoPlasma>(spaceObjects::oAmmoPlasma, location, randomizer::random(9.f, 15.f), 0.01f, randomizer::random(12.f, 15.f))
{
    setDamageSource(damageSource);
    velocity_ = velocity + direction*1500;
    location_ += velocity_*timer::frameTime()*1.2f;

    radius_ = randomizer::random(7.f, 11.f) * 3.f;

    // color_ = Color3f(randomizer::random(0.2f, 0.8f), randomizer::random(0.8f, 1.f), randomizer::random(0.0f, 0.6f));
    color_ = Color3f(randomizer::random(0.2f, 0.7f), randomizer::random(0.8f, 1.f), randomizer::random(0.9f, 1.f));

    trailEffects::attach(this, 0.05, 0.2f, radius_ * 2.5f, Color3f(0.04f, 0.31f, randomizer::random(0.28f, 0.35f)), false);
}

AmmoPlasma::~AmmoPlasma()
{
    trailEffects::detach(this);
}

void AmmoPlasma::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS | MOBILES | PARTICLES);
    Vector2f acceleration = physics::attract(this)*0.8f;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time + 0.1f*velocity_*time;

    lifeTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        particles::spawnMultiple(2, particles::pMud, location_, Vector2f(), Vector2f(), color_);
        int rand = randomizer::random(8, 20);
        sound::playSound(sound::BlubCollide, location_);
        // for (int i=0; i<rand; ++i)
        //     particles::spawn(particles::pMiniAmmoPlasma, location_, Vector2f(), Vector2f(), Color3f(), damageSource_);
    }
}

void AmmoPlasma::draw() const
{
    color_.gl4f(0.6f);
    // const int posX = 3, posY = 0;
    const int posX = 0, posY = 1;
    glTexCoord2f(posX*0.125f,     posY*0.125f);     glVertex2f(location_.x_-radius_, location_.y_-radius_);
    glTexCoord2f(posX*0.125f,     (posY+1)*0.125f); glVertex2f(location_.x_-radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, (posY+1)*0.125f); glVertex2f(location_.x_+radius_, location_.y_+radius_);
    glTexCoord2f((posX+1)*0.125f, posY*0.125f);     glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoPlasma::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    if (!isDead() && with->type() != spaceObjects::oAmmoPlasma /*&& with->type() != spaceObjects::oMiniAmmoPlasma*/)
    {
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
}

void AmmoPlasma::shockWave(Vector2f const& location, float strength, float radius)
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
