#include "Particles/Star.hpp"

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "defines.hpp"
#include "System/randomizer.hpp"


std::list<Star*> Star::activeParticles_;


Star::Star(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Star>(spaceObjects::oStar, location, 0.f, 0.f, 1.f)
{
    location_     += Vector2f::randDir()*randomizer::random(0.2f, 5.f);
    depth_        =  0.2f/(location-location_).lengthSquare();
    velocity_     =  (location_ - location)*depth_*0.005f;
    acceleration_ = velocity_*depth_*100.f;

    color_ = Color3f::random();
    color_.s(0.2f);
    alpha_ = 0.f;
}

void Star::update()
{
    update(timer::frameTime());
}

void Star::update(float time)
{
    if (location_.x_ < -radius_ || location_.x_ > settings::iMapXsize + radius_ ||
        location_.y_ < -radius_ || location_.y_ > settings::iMapYsize + radius_)
    {
        spawn(Vector2f(settings::iMapXsize*0.5f, settings::iMapYsize*0.5f), Vector2f(), Vector2f(), Color3f(), nullptr);
        killMe();
    }else
    {
        location_ += velocity_*time + acceleration_*time*time;
        velocity_ += acceleration_*time;
        radius_   += time*depth_*0.4f;

        alpha_ = radius_/16.f-0.5f;
        if (alpha_ > 1.f)  alpha_ = 1.f;
        if (alpha_ < 0.f)  alpha_ = 0.f;
    }
}

void Star::draw() const
{
    color_.gl4f(alpha_);
    glTexCoord2f(0, 0); glVertex2f(location_.x_-radius_, location_.y_-radius_);
    glTexCoord2f(0, 1); glVertex2f(location_.x_-radius_, location_.y_+radius_);
    glTexCoord2f(1, 1); glVertex2f(location_.x_+radius_, location_.y_+radius_);
    glTexCoord2f(1, 0); glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void Star::init()
{
    for (auto& it : activeParticles_)
        delete it;
    activeParticles_.clear();

    for (int i=0; i < settings::iStarField; ++i)
        spawn(Vector2f(settings::iMapXsize*0.5f, settings::iMapYsize*0.5f), Vector2f(), Vector2f(), Color3f(), nullptr);

    for (auto& it : activeParticles_)
        it->update(randomizer::random(0.f, 100.f));
}
