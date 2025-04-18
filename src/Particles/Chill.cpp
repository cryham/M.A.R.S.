#include "Particles/Chill.hpp"

#include "System/timer.hpp"
#include "System/randomizer.hpp"
#include <cmath>


std::list<Chill*> Chill::activeParticles_;


Chill::Chill(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Chill>(spaceObjects::oChill, location, randomizer::random(16.f, 40.f), 0.f, randomizer::random(0.6f, 0.8f))
    ,color_(color)
{
    Vector2f distortion(Vector2f::randDirLen());
    velocity_ = direction + distortion*150.f;
}

void Chill::update()
{
    float time = timer::frameTime();

    location_ += velocity_*time;
    velocity_ -= velocity_*time;
    // borders();

    lifeTime_ += time;
    if (lifeTime_ > totalLifeTime_)
        killMe();
}

void Chill::draw() const
{
    color_.gl4f(0.15f * sinf(M_PI * lifeTime_/totalLifeTime_));
    const float r = radius_ * 1.4f;
    const int u = 10, v = 0;

    uv8(u,   v);    glVertex2f(location_.x_ - r, location_.y_ - r);
    uv8(u,   v+2);  glVertex2f(location_.x_ - r, location_.y_ + r);
    uv8(u+2, v+2);  glVertex2f(location_.x_ + r, location_.y_ + r);
    uv8(u+2, v);    glVertex2f(location_.x_ + r, location_.y_ - r);
}
