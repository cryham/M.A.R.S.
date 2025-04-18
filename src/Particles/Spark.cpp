#include "Particles/Spark.hpp"

#include "System/timer.hpp"
#include "System/randomizer.hpp"


std::list<Spark*> Spark::activeParticles_;


Spark::Spark(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Spark>(spaceObjects::oSpark, location, 1, 0, randomizer::random(0.3f, 0.4f))
    ,color_(color)
{
    Vector2f distortion(Vector2f::randDirLen());
    velocity_ = direction + velocity_*0.5f + distortion*150.f;

    if (randomizer::random(0, 1) == 0)
        color_ = Color3f(1.0f, 0.8f, 0.0f);
}

void Spark::update()
{
    // update Color
    color_.v(-1.0/totalLifeTime_*lifeTime_+1);

    float time = timer::frameTime();

    location_ += velocity_*time;
    velocity_ -= velocity_*time;
    // borders();

    lifeTime_ += time;
}

void Spark::draw() const
{
    color_.gl4f();
    const int u = 0, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
