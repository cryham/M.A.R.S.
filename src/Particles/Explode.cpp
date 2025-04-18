#include "Particles/Explode.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<Explode*> Explode::activeParticles_;


Explode::Explode(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Explode>(spaceObjects::oExplode, location, 4, 0, randomizer::random(0.4f, 0.8f)) 
{
    velocity_ = Vector2f::randDir()*200*randomizer::random(0.5f, 2.f);

    color_.h(50.f);
    color_.v(0.8f);
    color_.s(0.3f);
}

void Explode::update()
{
    float time = timer::frameTime();

    // update Color
    color_.h((-1.0f/totalLifeTime_*lifeTime_+1.f)*60.f);
    color_.v(-0.8f/totalLifeTime_*lifeTime_+0.8f);
    color_.s(lifeTime_*10.f + 0.3f);

    // update Size
    radius_ = lifeTime_*50 + 2;

    location_ += velocity_*time;
    velocity_ += velocity_*(-6.f)*time;
    // borders();

    lifeTime_ += time;
}

void Explode::draw() const
{
    color_.gl4f(0.5);
    const int u = 6, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+2);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+2, v+2);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+2, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
