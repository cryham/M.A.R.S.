#include "Particles/Smoke.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<Smoke*> Smoke::activeParticles_;


Smoke::Smoke(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Smoke>(spaceObjects::oSmoke, location+Vector2f::randDirLen()*2.f,
        4, 0, randomizer::random(0.8f, 2.0f) * settings::iParticleLifeTime/100.f)
{
    color_ = Color3f(0.7, 0.7, 0.7);
}

void Smoke::update()
{
    float time = timer::frameTime();
    Vector2f acceleration = physics::attract(this);

    color_.v(-0.7f/totalLifeTime_*lifeTime_+0.7f);
    // update Size
    radius_ = lifeTime_*5.f+2;

    location_ = location_ + velocity_*time - 1.f*acceleration*time*time;
    velocity_ = velocity_ - 1.f*acceleration*time + velocity_*(-2)*time;

    lifeTime_ += time;
}

void Smoke::draw() const
{
    color_.gl4f(-0.3/totalLifeTime_*lifeTime_+0.3);
    const int u = 1, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void Smoke::shockWave(Vector2f const& location, float strength, float radius)
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
