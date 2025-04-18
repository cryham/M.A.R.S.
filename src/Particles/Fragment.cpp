#include "Particles/Fragment.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<Fragment*> Fragment::activeParticles_;


Fragment::Fragment(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<Fragment>(spaceObjects::oFragment, location, 2.f, 0.5f, randomizer::random(2.5f, 5.0f))
    ,color_(color)
{
    velocity_ = Vector2f::randDir()*300.f*randomizer::random(0.8f, 1.0f);
}

void Fragment::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS);
    Vector2f acceleration = physics::attract(this);

    location_ += velocity_*time + acceleration*time*time*2.f;
    velocity_ += acceleration*time*2.f;
    // borders();

    color_.v(-1.f/totalLifeTime_*lifeTime_+1.f);

    lifeTime_ += time;
}

void Fragment::draw() const
{
    color_.gl4f();
    glVertex2f(location_.x_, location_.y_);
}
