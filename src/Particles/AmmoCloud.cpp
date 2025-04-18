#include "Particles/AmmoCloud.hpp"

#include "SpaceObjects/physics.hpp"
#include "System/timer.hpp"
#include "Particles/particles.hpp"
#include "System/randomizer.hpp"
#include <cmath>


std::list<AmmoCloud*> AmmoCloud::activeParticles_;


AmmoCloud::AmmoCloud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoCloud>(spaceObjects::oAmmoCloud, location, randomizer::random(19.f, 25.f), 0.01f, randomizer::random(2.f, 4.f))
{
    cloud_ = true;
    setDamageSource(damageSource);
    spawnTime_ = 0.f;

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

    physics::overlap(this, MOBILES | STATICS);
    // Vector2f acceleration; // = physics::attract(this)*0.8f;  //..add?

    location_ += velocity_*time;  // + acceleration*time*time;
    // velocity_ += acceleration*time + 0.1f*velocity_*time;
    Vector2f const dir(velocity_.normalize());
    velocity_ += acceleration_ * dir * time;
    radius_ = 84.f + 120.4f * lifeTime_ / totalLifeTime_;
    borders();

    lifeTime_ += time;
    spawnTime_ += time;

    if (lifeTime_ > totalLifeTime_)
        killMe();
    else
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
    const float r = radius_, r2 = radius_ * 1.3f;
    // color_.gl4f(0.1f - 0.1f * lifeTime_ / totalLifeTime_);
    color_.gl4f(0.4f * (0.7f + 0.3f * sinf(2.f * lifeTime_ / totalLifeTime_ * M_PI)));
    const int u = 0, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_ - r, location_.y_ - r);
    uv8(u,   v+1);  glVertex2f(location_.x_ - r, location_.y_ + r);
    uv8(u+1, v+1);  glVertex2f(location_.x_ + r, location_.y_ + r);
    uv8(u+1, v);    glVertex2f(location_.x_ + r, location_.y_ - r);
    
    color_.gl4f(0.3f * sinf(lifeTime_ / totalLifeTime_ * M_PI));
    const int u2 = 10, v2 = 0;
    uv8(u2,   v2);    glVertex2f(location_.x_ - r2, location_.y_ - r2);
    uv8(u2,   v2+2);  glVertex2f(location_.x_ - r2, location_.y_ + r2);
    uv8(u2+2, v2+2);  glVertex2f(location_.x_ + r2, location_.y_ + r2);
    uv8(u2+2, v2);    glVertex2f(location_.x_ + r2, location_.y_ - r2);
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
