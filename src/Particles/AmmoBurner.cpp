#include "Particles/AmmoBurner.hpp"

#include "System/timer.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Media/sound.hpp"
#include "System/randomizer.hpp"


std::list<AmmoBurner*> AmmoBurner::activeParticles_;


AmmoBurner::AmmoBurner(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoBurner>(spaceObjects::oAmmoBurner, location, 1.f, 0.f, randomizer::random(0.4f, 0.5f))
{
    setDamageSource(damageSource);
    Vector2f distortion(Vector2f::randDirLen()*3.f);
    location_ = location + direction*randomizer::random(0.f, 20.f);
    velocity_ = velocity + direction*700.f + distortion*70.f;

    color_.h(50.f);
    color_.v(0.8f);
    color_.s(0.3f);
}

void AmmoBurner::update()
{
    float time = timer::frameTime();
    physics::collide(this, STATICS);
    // update Color
    color_.h((-1.0f/totalLifeTime_*lifeTime_+1.f)*60.f);
    color_.v(-0.8f/totalLifeTime_*lifeTime_+0.8f);
    color_.s(lifeTime_*10.f + 0.3f);

    // update Size
    radius_ = lifeTime_*50 + 2;

    location_ += velocity_*time;
    velocity_ += velocity_*(-4.f)*time;
    borders();

    lifeTime_ += time;

    //  collisions with ships
    const auto& shipsList = ships::getShips();
    for (const auto& it : shipsList)
        if ((location_ - it->location()).lengthSquare() < std::pow(radius_ + it->radius(), 2) && it->collidable())
            it->onCollision(this, location_, velocity_, velocity_);

    //  collisions with ball
    Ball* ball = balls::getBall();
    if (ball)
        if ((location_ - ball->location()).lengthSquare() < std::pow(radius_ + ball->radius(), 2))
            ball->onCollision(this, location_, velocity_, velocity_);
}

//  draw
void AmmoBurner::draw() const
{
    color_.gl4f();
    const int u = 0, v = 0;
    uv8(u,   v);    glVertex2f(location_.x_-radius_, location_.y_-radius_);
    uv8(u,   v+1);  glVertex2f(location_.x_-radius_, location_.y_+radius_);
    uv8(u+1, v+1);  glVertex2f(location_.x_+radius_, location_.y_+radius_);
    uv8(u+1, v);    glVertex2f(location_.x_+radius_, location_.y_-radius_);
}

void AmmoBurner::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    killMe();
}
