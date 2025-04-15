/* AmmoPlasma.cpp

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

#include "Particles/AmmoPlasma.hpp"

#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoPlasma*> AmmoPlasma::activeParticles_;


AmmoPlasma::AmmoPlasma(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoPlasma>(spaceObjects::oAmmoPlasma, location,
        randomizer::random(9.f, 15.f), 0.01f, randomizer::random(12.f, 15.f))
{
    setDamageSource(damageSource);
    velocity_ = velocity + direction * 1500;
    location_ += velocity_ * timer::frameTime()*1.2f;

    radius_ = randomizer::random(7.f, 11.f) * 3.f;

    color_ = Color3f(randomizer::random(0.3f, 0.7f), randomizer::random(0.8f, 1.f), randomizer::random(0.9f, 1.f));

    trailEffects::attach(this, 0.05, 0.15f, radius_ * 3.f, Color3f(0.04f, 0.31f, randomizer::random(0.28f, 0.35f)), false);
}

AmmoPlasma::~AmmoPlasma()
{
    trailEffects::detach(this);
}

void AmmoPlasma::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS | MOBILES);  // | PARTICLES);
    Vector2f acceleration = physics::attract(this)*0.8f;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time + 0.1f*velocity_*time;
    borders();

    lifeTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        particles::spawnMultiple(2, particles::pMud, location_, Vector2f(), Vector2f(), color_);
        int rand = randomizer::random(8, 20);
        sound::playSound(sound::BlubCollide, location_);
        // for (int i=0; i < rand; ++i)
        //     particles::spawn(particles::pMiniAmmoPlasma, location_, Vector2f(), Vector2f(), Color3f(), damageSource_);
    }
}

//  draw
void AmmoPlasma::draw() const
{
    const int u = 8, v = 0;
    const float
        angle [3] = {12.f,-17.f, 31.f},
        radius[3] = {1.6f, 1.2f, 0.5f},
        alpha [3] = {0.3f, 0.4f, 0.3f};
    
    for (int i=0; i < 3; ++i)
    {
        float a = lifeTime_ * angle[i];
        Vector2f dir(cosf(a), -sinf(a));
        
        dir *= radius_ * radius[i];
        Vector2f side(dir.y_, -dir.x_);
        
        const Vector2f
            topL(location_ + dir + side),
            topR(location_ + dir - side),
            btmL(location_ - dir + side),
            btmR(location_ - dir - side);

        // if (i==2)
        //     glColor4f(0.8f, 0.95f, 1.f, alpha[i]);
        //     color_.brightened().gl4f(alpha[i]);
        // else
            color_.gl4f(alpha[i]);
        uv8(u,   v+2);  glVertex2f(topL.x_, topL.y_);
        uv8(u+2, v+2);  glVertex2f(btmL.x_, btmL.y_);
        uv8(u+2, v);    glVertex2f(btmR.x_, btmR.y_);
        uv8(u,   v);    glVertex2f(topR.x_, topR.y_);
    }
}

void AmmoPlasma::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    if (!isDead() && with->type() >= spaceObjects::oPlanet && with->type() <= spaceObjects::oBall)
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
