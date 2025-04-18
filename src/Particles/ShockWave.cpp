#include "Particles/ShockWave.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


std::list<ShockWave*> ShockWave::activeParticles_;


ShockWave::ShockWave(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<ShockWave>(spaceObjects::oShockWave, location, 4, 0, randomizer::random(0.6f, 1.f))
{   }

void ShockWave::update()
{
    float time = timer::frameTime();

    // update Size
    radius_ = lifeTime_*700+20;

    lifeTime_ += time;
}

void ShockWave::draw() const
{
    glColor4f(1.f, 1.f, 1.f, 1.f - lifeTime_/totalLifeTime_);
    glTexCoord2f(0, 0); glVertex2f(location_.x_-radius_, location_.y_-radius_);
    glTexCoord2f(0, 1); glVertex2f(location_.x_-radius_, location_.y_+radius_);
    glTexCoord2f(1, 1); glVertex2f(location_.x_+radius_, location_.y_+radius_);
    glTexCoord2f(1, 0); glVertex2f(location_.x_+radius_, location_.y_-radius_);
}
