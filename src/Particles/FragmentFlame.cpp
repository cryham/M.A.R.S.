#include "Particles/FragmentFlame.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<FragmentFlame*> FragmentFlame::activeParticles_;


FragmentFlame::FragmentFlame(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<FragmentFlame>(spaceObjects::oFragmentFlame, location, 1.f, 0.f, randomizer::random(0.15f, 0.25f))
{
    Vector2f distortion(Vector2f::randDirLen());
    location_ = location + distortion;
    velocity_ = velocity*0.5f + distortion*20.f;

    radius_ = randomizer::random(1.f, 3.f);

    color_.h(50.f);
    color_.v(0.6f);
    color_.s(0.8f);
}

void FragmentFlame::update()
{
    float time = timer::frameTime();
    // update Color
    color_.h((-1.0/totalLifeTime_*lifeTime_+1)*60+350);
    color_.v(-1.0/totalLifeTime_*lifeTime_+1);

   // radius_ += time*20;

    location_ += velocity_*time;
    velocity_ += velocity_*(-10.f)*time;
    // borders();

    lifeTime_ += time;
}

void FragmentFlame::draw() const
{
    color_.gl4f();
    const int u = 5, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
