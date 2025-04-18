#include "Particles/HeatJet.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<HeatJet*> HeatJet::activeParticles_;


HeatJet::HeatJet(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource):
           Particle<HeatJet>(spaceObjects::oHeatJet, location, 1.f, 0.f, randomizer::random(0.5f, 1.0f))
{
    Vector2f distortion(Vector2f::randDirLen());
    location_ = location + distortion;
    velocity_ = velocity + direction*(-60.f) + distortion*20.f;
}

void HeatJet::update()
{
    float time = timer::frameTime();

    // update Size
    radius_ = lifeTime_*30 + 1;

    location_ += velocity_*time;
    borders();

    lifeTime_ += time;
}

void HeatJet::draw() const
{
    glColor4f(1.f, 1.f, 1.f, 1.f - lifeTime_/totalLifeTime_);
    const int u = 3, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+2);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+2, v+2);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+2, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
