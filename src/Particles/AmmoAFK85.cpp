#include "Particles/AmmoAFK85.hpp"

#include "SpaceObjects/physics.hpp"
#include "System/Color3f.hpp"
#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"


std::list<AmmoAFK85*> AmmoAFK85::activeParticles_;


AmmoAFK85::AmmoAFK85(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoAFK85>(spaceObjects::oAmmoAFK85, location, 1.f, 0.3f, 2.5f)
{
    setDamageSource(damageSource);
    // color_ = damageSource->team()->color();  // team's color
    // color_ = damageSource->color();  // player's color
    // color_ = Color3f(0.8f, 0.6f, 1.f);
    if (damageSource)
        color_ = damageSource->color() * 0.5f + 0.5f * Color3f(0.8f, 0.6f, 1.f);
    else
        color_ = Color3f(0.8f, 0.6f, 1.f);

    Vector2f distortion(Vector2f::randDir());
    velocity_ = direction*1000.f + distortion*17.f;
    location_ += velocity_*timer::frameTime()*1.2f;
}

void AmmoAFK85::update()
{
    float time = timer::frameTime();
    physics::collide(this, STATICS | MOBILES);
    Vector2f acceleration = physics::attract(this)*10.f;

    location_ += velocity_*time + acceleration*time*time;
    velocity_ += acceleration*time;
    borders();

    lifeTime_ += time;
}

//  draw
void AmmoAFK85::draw() const
{
    color_.gl4f();

    Vector2f dir(velocity_ * 0.016f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    side *= 0.1f;

    const Vector2f
        topL(location_ + dir + side),
        topR(location_ + dir - side),
        btmL(location_ - 3*dir + side),
        btmR(location_ - 3*dir - side);

    const int u = 0, v = 2;
    uv8(u,   v);       glVertex2f(topL.x_, topL.y_);
    uv8(u,   v+0.5f);  glVertex2f(btmL.x_, btmL.y_);
    uv8(u+3, v+0.5f);  glVertex2f(btmR.x_, btmR.y_);
    uv8(u+3, v);       glVertex2f(topR.x_, topR.y_);
}

void AmmoAFK85::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity-velocity_).length();
    if (strength > 50.f)
    {
        switch (with->type())
        {
            case spaceObjects::oShip:
                sound::playSound(sound::LaserCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oBall:
                sound::playSound(sound::LaserCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oPlanet: case spaceObjects::oHome:
                sound::playSound(sound::LaserCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oSun:
                sound::playSound(sound::LaserCollide, location, (strength-50)/3);
                break;

            default:;
        }
    }
    if (with->type() != spaceObjects::oMiniAmmoFlubba)
        killMe();
}
