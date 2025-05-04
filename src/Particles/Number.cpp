#include "Particles/Number.hpp"

#include "System/timer.hpp"
#include "Media/text.hpp"

#include <sstream>


std::list<Number*> Number::activeParticles_;


Number::Number(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Number>(spaceObjects::oNumber, location, 4, 0, 1.f)
    ,alpha_(1.f)
{
    velocity_ = velocity;
    float len = velocity.length(), max = 900.f;  // limit vel len
    if (len > max)
        velocity_ = velocity.normalize() * max;

    value_ = direction.x_ / 10.f;

    radius_ = direction.y_;
    if (radius_ > 40.f)
        radius_ = 40.f;

    if (value_ > 0)
        color_ = Color3f(0.4f, 1.0f, 0.4f);
    else
        color_ = Color3f(1.0f, 0.4f, 0.4f);
}

void Number::update()
{
    float time = timer::frameTime();

    alpha_ = 1.f-1.f/totalLifeTime_*lifeTime_;

    location_ = location_ + velocity_*time;
    velocity_ = velocity_ + velocity_*(-5.f)*time;

    lifeTime_ += time;
}

void Number::draw() const
{
    std::stringstream sstr;
    sstr << value_;
    text::drawMobileSpaceText(sf::String(sstr.str()), location_, radius_, TEXT_ALIGN_CENTER, color_, alpha_);
}
