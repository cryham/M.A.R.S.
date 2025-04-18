#include "Particles/AmmoShotgun2.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "System/randomizer.hpp"


std::list<AmmoShotgun2*> AmmoShotgun2::activeParticles_;


AmmoShotgun2::AmmoShotgun2(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource)
    :Particle<AmmoShotgun2>(spaceObjects::oAmmoShotgun2, location, 2.5f, 0.5f, randomizer::random(0.3f, 0.7f))
    ,color_(1.f, 0.4f, 0.3f)
{
    setDamageSource(damageSource);
    velocity_ = direction * 1000.f + Vector2f::randDirLen() * 400.f;
    location_ += velocity_ * timer::frameTime()*1.2f;

    trailEffects::attach(this, 0.02f, 0.1f, 4.f, Color3f(0.2f, 0.1f, 0.25f), false);
}

AmmoShotgun2::~AmmoShotgun2()
{
    trailEffects::detach(this);
}

void AmmoShotgun2::update()
{
    float time = timer::frameTime();

    physics::collide(this, STATICS | MOBILES);
    Vector2f acceleration = physics::attract(this)*15;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time - velocity_*time;
    borders();

    color_.v(-1.f/totalLifeTime_*lifeTime_+1.f);

    lifeTime_ += time;
}

void AmmoShotgun2::draw() const
{
    color_.gl4f();
    const int u = 0, v = 1;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoShotgun2::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity-velocity_).length();

    if (strength > 50.f)
    {
        switch (with->type())
        {
            case spaceObjects::oShip:
                sound::playSound(sound::Particle, location, (strength-50)/3);
                break;

            case spaceObjects::oBall:
                sound::playSound(sound::Particle, location, (strength-50)/3);
                break;

            case spaceObjects::oPlanet: case spaceObjects::oHome:
                sound::playSound(sound::Particle, location, (strength-50)/3);
                break;

            case spaceObjects::oSun:
                sound::playSound(sound::Particle, location, (strength-50)/3);
                break;

            default:;
        }
    }
}
