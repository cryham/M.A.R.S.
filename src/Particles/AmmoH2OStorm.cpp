/* AmmoH2OStorm.cpp

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

#include "Particles/AmmoH2OStorm.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "System/randomizer.hpp"
#include "Media/sound.hpp"


std::list<AmmoH2OStorm*> AmmoH2OStorm::activeParticles_;


AmmoH2OStorm::AmmoH2OStorm(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoH2OStorm>(spaceObjects::oAmmoH2OStorm, location, 8.f /*R*/, 0.4f /*mass*/, randomizer::random(9.f, 11.f) /*life*/)
{
    setDamageSource(damageSource);
    velocity_ = velocity + direction*1100.f + Vector2f::randDirLen()*150.f;
    location_ += velocity_*timer::frameTime()*1.2f;

    radius_ = randomizer::random(15.f, 23.f);

    color_ = 0.7f * Color3f(randomizer::random(0.4f, 0.8f), randomizer::random(0.7f, 1.f), randomizer::random(0.9f, 1.0f));
    // index_ = rand() % 6;  //3
    index_ = 3 + rand() % 3;
}


void AmmoH2OStorm::update()
{
    float time = timer::frameTime();

    Vector2f acceleration = physics::attract(this);
    physics::collide(this, STATICS | MOBILES | PARTICLES);

    // update Size
    if (lifeTime_ > totalLifeTime_-0.3f)
        radius_ = -400.0f*pow(lifeTime_+0.2f-totalLifeTime_, 2)+9.f;

    location_ += velocity_*time + acceleration*time*time*5.f;
    velocity_ += acceleration*time*7.f;
    borders();

    lifeTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        particles::spawnMultiple(2, particles::pMud, location_, Vector2f(), Vector2f(), color_);
    }
}

void AmmoH2OStorm::draw() const
{
    const float r = radius_ * 1.3f;
    color_.gl4f(0.6f);  // alpha
    if (index_ >= 3)
    {   const int u = 6 + 2 * (index_-3), v = 0;
        uv8(u,   v);    glVertex2f(location_.x_ - r, location_.y_ - r);
        uv8(u,   v+2);  glVertex2f(location_.x_ - r, location_.y_ + r);
        uv8(u+2, v+2);  glVertex2f(location_.x_ + r, location_.y_ + r);
        uv8(u+2, v);    glVertex2f(location_.x_ + r, location_.y_ - r);
    }else
    {   const int u = index_, v = 0;
        uv8(u,   v);    glVertex2f(location_.x_ - r, location_.y_ - r);
        uv8(u,   v+1);  glVertex2f(location_.x_ - r, location_.y_ + r);
        uv8(u+1, v+1);  glVertex2f(location_.x_ + r, location_.y_ + r);
        uv8(u+1, v);    glVertex2f(location_.x_ + r, location_.y_ - r);
    }
}

void AmmoH2OStorm::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    if (!isDead() && with->type() != spaceObjects::oAmmoH2OStorm)
    {
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }
}
