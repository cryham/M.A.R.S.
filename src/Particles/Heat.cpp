#include "Particles/Heat.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<Heat*> Heat::activeParticles_;


Heat::Heat(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Heat>(spaceObjects::oHeat, location+Vector2f::randDirLen()*2.f,
        4, 0, randomizer::random(0.8f, 2.0f) * settings::iParticleLifeTime/100.f)
{   }

void Heat::update()
{
    float time = timer::frameTime();
    Vector2f acceleration = physics::attract(this);

    // update Size
    radius_ = lifeTime_*10.f+10;

    location_ = location_ + velocity_*time - 2.f*acceleration*time*time;
    velocity_ = velocity_ - 2.f*acceleration*time + velocity_*(-2)*time;

    lifeTime_ += time;
}

void Heat::draw() const
{
    glColor4f(1.f, 1.f, 1.f, 1.f - lifeTime_/totalLifeTime_);
    const int u = 3, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+2);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+2, v+2);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+2, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
