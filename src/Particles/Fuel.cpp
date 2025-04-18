#include "Particles/Fuel.hpp"

#include "System/timer.hpp"
#include "System/randomizer.hpp"


std::list<Fuel*> Fuel::activeParticles_;


Fuel::Fuel(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Fuel>(spaceObjects::oFuel, location, 1.f, 0.f, randomizer::random(0.2f, 0.4f))
{
    Vector2f distortion(Vector2f::randDirLen());
    location_ = location + distortion;
    velocity_ = velocity + direction*(-90.f) + distortion*30.f;

    color_.h(150.f);
    color_.v(0.6f);
    color_.s(0.8f);
}

void Fuel::update()
{
    float time = timer::frameTime();
    physics::collide(this, STATICS);
    // update Color
    color_.h((1.f/totalLifeTime_*lifeTime_+1.f)*60.f+150.f);
    color_.v(-0.6f/totalLifeTime_*lifeTime_+0.6f);
    color_.s(lifeTime_/100.f + 0.8f);

    // update Size
    radius_ = -lifeTime_*10 + 5;

    location_ += velocity_*time;
    velocity_ += velocity_*(-1.f)*time;
    // borders();

    lifeTime_ += time;
}

void Fuel::draw() const
{
    color_.gl4f();
    const int u = 0, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
