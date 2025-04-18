#include "Particles/Eruption.hpp"

#include "System/timer.hpp"
#include "System/randomizer.hpp"


std::list<Eruption*> Eruption::activeParticles_;


Eruption::Eruption(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Eruption>(spaceObjects::oEruption, location, 1.f, 0.f, randomizer::random(1.0f, 2.5f))
    ,color_(color)
{
    Vector2f distortion(Vector2f::randDir() * randomizer::random(0.7f, 1.1f));
    velocity_ = velocity * 50.f + distortion * 70.f;
}

void Eruption::update()
{
    // update Color
    color_.v(-1.0f/totalLifeTime_*lifeTime_+1.f);

    float time = timer::frameTime();
    Vector2f acceleration = physics::attract(this);

    location_ += velocity_*time + acceleration*0.5*time*time;
    velocity_ += acceleration *0.5*time + velocity_ * -2.f*time;
    // borders();

    lifeTime_ += time;
}

void Eruption::draw() const
{
    color_.gl4f();
    const int u = 0, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
