#include "Particles/AmmoFreezers.hpp"

#include "SpaceObjects/physics.hpp"
#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "Particles/particles.hpp"
#include "System/randomizer.hpp"


std::list<AmmoFreezers*> AmmoFreezers::activeParticles_;


AmmoFreezers::AmmoFreezers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoFreezers>(spaceObjects::oAmmoFreezers, location,
        randomizer::random(9.f, 15.f), 0.01f, randomizer::random(12.f, 15.f))
{
    cloud_ = true;
    setDamageSource(damageSource);
    spawnTime_ = 0.f;
    Vector2f side(direction.y_, -direction.x_);

    velocity_ = velocity + direction * 900 + 100.f * side * randomizer::random(-1.f, 1.f);
    location_ += velocity_ * timer::frameTime()*1.2f;

    radius_ = randomizer::random(7.f, 12.f) * 4.f;

    color_ = Color3f(randomizer::random(0.2f, 0.4f), randomizer::random(0.6f, 0.8f), 1.f);

    // trailEffects::attach(this, 0.02, 0.1f, radius_ * 2.5f, Color3f(0.14f, randomizer::random(0.21f, 0.35f), 0.35f), false);
}

AmmoFreezers::~AmmoFreezers()
{
    // trailEffects::detach(this);
}

//  update
void AmmoFreezers::update()
{
    float time = timer::frameTime();

    physics::overlap(this, MOBILES | STATICS);
    Vector2f acceleration = physics::attract(this) * 0.8f;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time - 0.1f*velocity_*time;
    radius_ -= 1.2f * time * lifeTime_ / totalLifeTime_;
    borders();

    lifeTime_ += time;
    spawnTime_ += time;

    if (lifeTime_ > totalLifeTime_)
    {
        killMe();
    }
    else if (lifeTime_ < 2)
    {
        if (spawnTime_ > 0.1f)
        {   spawnTime_ = 0.f;

            Vector2f dir = Vector2f::randDir();
            float len = randomizer::random(1.f, radius_ * 0.2f);

            particles::spawnMultiple(0.3f,
                             particles::pMud,   location_ + dir * len, dir, dir * len * 15.2f, color_);
            particles::spawn(particles::pChill, location_ + dir * len, dir, dir * len * 0.2f, color_);
        }
    }
}

void AmmoFreezers::draw() const
{
    const float r = radius_ * 0.7f, r2 = radius_ * 1.3f, r3 = radius_ * 1.8f;

    color_.gl4f(0.1f);
    const int u = 10, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_ - r, location_.y_ - r);
    uv8(u,   v+2);  glVertex2f(location_.x_ - r, location_.y_ + r);
    uv8(u+2, v+2);  glVertex2f(location_.x_ + r, location_.y_ + r);
    uv8(u+2, v);    glVertex2f(location_.x_ + r, location_.y_ - r);
    color_.gl4f(0.6f);

    color_.gl4f(0.2f);
    const int u2 = 8;
    uv8(u2,   v);    glVertex2f(location_.x_ - r2, location_.y_ - r2);
    uv8(u2,   v+2);  glVertex2f(location_.x_ - r2, location_.y_ + r2);
    uv8(u2+2, v+2);  glVertex2f(location_.x_ + r2, location_.y_ + r2);
    uv8(u2+2, v);    glVertex2f(location_.x_ + r2, location_.y_ - r2);

    color_.brightened().gl4f(0.2f);
    const int u3 = 6;
    uv8(u3,   v);    glVertex2f(location_.x_ - r3, location_.y_ - r3);
    uv8(u3,   v+2);  glVertex2f(location_.x_ - r3, location_.y_ + r3);
    uv8(u3+2, v+2);  glVertex2f(location_.x_ + r3, location_.y_ + r3);
    uv8(u3+2, v);    glVertex2f(location_.x_ + r3, location_.y_ - r3);
}

void AmmoFreezers::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    // no
}
