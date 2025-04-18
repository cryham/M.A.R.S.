#include "Particles/Electric.hpp"

#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "System/randomizer.hpp"


std::list<Electric*> Electric::activeParticles_;


Electric::Electric(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Electric>(spaceObjects::oElectric, location, randomizer::random(31.f, 75.f), 0.f, randomizer::random(0.3f, 0.5f))
    ,color_(color)
{
    Vector2f distortion(Vector2f::randDirLen());
    velocity_ = direction + velocity_*120.f + distortion*150.f;
}

void Electric::update()
{
    // color_.v(0.5f - 0.5f * lifeTime_/totalLifeTime_);

    float time = timer::frameTime();

    location_ += velocity_*time;
    velocity_ -= velocity_*time;
    // borders();

    lifeTime_ += time;
    if (lifeTime_ > totalLifeTime_)
        killMe();
}

void Electric::draw() const
{
    color_.gl4f( 0.15f + 0.1f * sinf(1.4f * lifeTime_));
    const float r = radius_ * (1.f + 1.3f * lifeTime_);
    const int u = 8 + ((int)(lifeTime_ * 46.f) % 4) * 2, v = 2;
    
    uv8(u,   v+4);  glVertex2f(location_.x_ - r, location_.y_ - r);
    uv8(u+2, v+4);  glVertex2f(location_.x_ - r, location_.y_ + r);
    uv8(u+2, v);    glVertex2f(location_.x_ + r, location_.y_ + r);
    uv8(u,   v);    glVertex2f(location_.x_ + r, location_.y_ - r);

    color_.gl4f( 0.15f + 0.1f * cosf(2.1f * lifeTime_));
    const float r2 = radius_* (0.3f + 1.5f * lifeTime_);
    const int u2 = 6, v2 = 0;
    uv8(u2,   v2);    glVertex2f(location_.x_ - r2, location_.y_ - r2);
    uv8(u2,   v2+2);  glVertex2f(location_.x_ - r2, location_.y_ + r2);
    uv8(u2+2, v2+2);  glVertex2f(location_.x_ + r2, location_.y_ + r2);
    uv8(u2+2, v2);    glVertex2f(location_.x_ + r2, location_.y_ - r2);
}
