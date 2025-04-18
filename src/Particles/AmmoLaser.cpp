#include "Particles/AmmoLaser.hpp"

#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/Trail.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "defines.hpp"


std::list<AmmoLaser*> AmmoLaser::activeParticles_;


AmmoLaser::AmmoLaser(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoLaser>(spaceObjects::oAmmoLaser, location, 1.f, 0.0001f, 3.0f)
{
    for (int i=0; i < steps_; ++i)
        pos_[i] = location;
    setDamageSource(damageSource);
    velocity_ = direction * 610.f;
    location_ += velocity_ * timer::frameTime() * 1.1f;

    trail_ = trailEffects::attach(this, 0.01f, 0.02f, 22.f, 0.6f * Color3f(0.4f, 0.2f, 0.1f), true);
}

AmmoLaser::~AmmoLaser()
{
    trailEffects::detach(this);
}


void AmmoLaser::update()
{
    float time = timer::frameTime();
    // float time = timer::frameTime()/steps_;  // slow-

    for (int i=0; i < steps_; ++i)
    {
        pos_[i] = location_;
        physics::collide(this, STATICS | MOBILES);
        location_ += velocity_ * time;
        borders();
        lifeTime_ += time;

        if (i != steps_-1)
            trail_->update();
    }
}

//  draw
void AmmoLaser::draw() const
{
    // only trail
}


void AmmoLaser::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    // no
}
