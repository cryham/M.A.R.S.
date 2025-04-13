/* AmmoSeekers.cpp

Copyright (c) 2025 Crystal Hammer
Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "Particles/AmmoSeekers.hpp"

#include "SpaceObjects/spaceObjects.hpp"
#include "System/Color3f.hpp"
#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Particles/particles.hpp"
#include "System/settings.hpp"
#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ball.hpp"
#include "SpaceObjects/balls.hpp"
#include "Shaders/postFX.hpp"
#include "Players/Player.hpp"
#include "System/randomizer.hpp"

#include <cfloat>
using namespace std;


list<AmmoSeekers*> AmmoSeekers::activeParticles_;


AmmoSeekers::AmmoSeekers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoSeekers>(spaceObjects::oAmmoSeekers, location, 5.f, 1.0f, 1000.f)
    ,timer_(0.5f)  // 1.f target homing delay
    ,shipTarget_(NULL)
    ,ballTarget_(NULL)
    ,parent_(damageSource)
    ,rotation_(0.f)
    ,life_(10.f)
    ,frozen_(0.f)
    ,visible_(true)
{
    setDamageSource(damageSource);
    velocity_ = direction * 600.f;
    location_ += velocity_ * timer::frameTime()*1.2f;

    color_ = Color3f(randomizer::random(0.3f, 0.6f), randomizer::random(0.7f, 0.9f), randomizer::random(0.2f, 0.5f));
    // trailEffects::attach(this, 0.02, 0.2f, 20.f, color_, false); //Color3f(0.5f, 0.8f, 0.f), false);
    trailEffects::attach(this, 0.02, 0.2f, 20.f, parent_->color() * 0.7f, false);
}

AmmoSeekers::~AmmoSeekers()
{
    trailEffects::detach(this);
}


void AmmoSeekers::update()
{
    float const time = timer::frameTime();

    if (frozen_ <= 0)
    {
        physics::collide(this, STATICS | MOBILES | PARTICLES);

        if (shipTarget_ || ballTarget_)
        {
            MobileSpaceObject* target(NULL);
            if (ballTarget_)
                target = ballTarget_;
            else if (shipTarget_)
                target = shipTarget_;

            float const speed(velocity_.length());
            velocity_ /= speed;
            Vector2f const toTarget(target->location() - location_);
            rotation_ = toTarget.y_*velocity_.x_ - toTarget.x_*velocity_.y_;
            float const phi(time * 3.5f);  // max turn homing
            
            if (rotation_ > 0.f)
                velocity_ = Vector2f (cos(atan2(velocity_.y_, velocity_.x_)+phi), sin(atan2(velocity_.y_, velocity_.x_)+phi));
            else
                velocity_ = Vector2f (cos(atan2(velocity_.y_, velocity_.x_)-phi), sin(atan2(velocity_.y_, velocity_.x_)-phi));
            velocity_ *= 600.f;  // speed

            if (shipTarget_ && dynamic_cast<Ship*>(shipTarget_)->getLife() <= 0.f)
                shipTarget_ = NULL;
            else
            if (ballTarget_ && !(dynamic_cast<Ball*>(ballTarget_)->isVisible()))
                ballTarget_ = NULL;
        }

        location_ += velocity_ * time;
        borders();

        Vector2f const dir(velocity_.normalize());

        // particles::spawnTimed(80.f/settings::C_globalParticleCount, particles::pFuel, location_ - dir * radius_ * 2.3f, dir, velocity_);
        particles::spawnTimed(5.f/settings::C_globalParticleCount, particles::pHeatJet, location_ - dir * radius_ * 3.f, dir, velocity_);

        lifeTime_ += time;
        timer_ -= time;

        if (timer_ < 0.f)
        {
            timer_ = 0.5f;

            ballTarget_ = NULL;
            shipTarget_ = NULL;

            vector<Ship*> const& ships (ships::getShips());
            float closest(FLT_MAX);
            for (const auto& it : ships)
            {
                float distance((location_ - it->location()).lengthSquare());
                if (distance < closest && it->collidable() &&
                    it->getOwner() != parent_ &&  // dont aim at self
                    it->getOwner()->team() != parent_->team())  // or same team
                {
                    shipTarget_ = it;
                    closest = distance;
                }
            }

            Ball* ball(balls::getBall());
            if (ball)
            {
                float distance((location_ - ball->location()).lengthSquare());
                if (distance < closest && ball->isVisible())
                {
                    ballTarget_ = ball;
                    shipTarget_ = NULL;
                }
            }
        }
    }else
    {
        physics::collide(this, STATICS | MOBILES | PARTICLES);

        frozen_  -= time*3.f;
        life_    -= time*5.f;

        if (frozen_ < 0.f)
        {   frozen_ = 0.f;
            mass_ = 3.f;
            particles::spawnMultiple(2, particles::pCrushedIce, location_);
        }
    }

    if (life_ <= 0.f)
    {
        visible_ = false;
        // particles::spawnMultiple(5, particles::pDust, location_);
        // particles::spawnMultiple(3, particles::pHeatJet, location_);
        particles::spawnMultiple(2, particles::pMud, location_);
        particles::spawnMultiple(1, particles::pSpark, location_);

        // postFX::onExplosion();
        setDamageSource(parent_);
        // physics::  causeShockWave(damageSource(), location_, 150.f, 300.f, 3.f);
        // particles::spawn(particles::pShockWave, location_);
        killMe();
    }
}

void AmmoSeekers::draw() const
{
    color_.gl4f();

    Vector2f dir(velocity_.normalize() * 3.f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    const Vector2f
        topL(location_ + dir + side),
        topR(location_ + dir - side),
        btmL(location_ - 3*dir + side),
        btmR(location_ - 3*dir - side);

    const int posX = 0;
    const int posY = 5;  //3
    uv8(posX,   posY+2);  glVertex2f(topL.x_, topL.y_);
    uv8(posX+4, posY+2);  glVertex2f(btmL.x_, btmL.y_);
    uv8(posX+4, posY);    glVertex2f(btmR.x_, btmR.y_);
    uv8(posX,   posY);    glVertex2f(topR.x_, topR.y_);

    MobileSpaceObject* target(NULL);
    if (ballTarget_)
        target = ballTarget_;
    else if (shipTarget_)
        target = shipTarget_;

    if (target && frozen_ <= 0)
    {
        glColor3f(1.f, 0.7f, 0.9f);
        const int posX = 5;
        const int posY = 5;
        float const size = sin(lifeTime_*5.f)*4.f + 26.f;
        Vector2f const loc(target->location());

        uv8(posX,   posY+3);  glVertex2f(loc.x_ - size, loc.y_ - size);
        uv8(posX+3, posY+3);  glVertex2f(loc.x_ + size, loc.y_ - size);
        uv8(posX+3, posY);    glVertex2f(loc.x_ + size, loc.y_ + size);
        uv8(posX, posY);      glVertex2f(loc.x_ - size, loc.y_ + size);
    }
}

void AmmoSeekers::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength(velocity.length());
    float amount(0.f), unfreeze(0.f);

    switch (with->type())
    {
        case spaceObjects::oAmmoAFK47:
        case spaceObjects::oAmmoAFK85:
            amount = strength*0.01f;
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoShotgun:
        case spaceObjects::oAmmoShotgun2:
            amount = strength*0.01f;
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoH2OMG:
        case spaceObjects::oAmmoH2OStorm:
        case spaceObjects::oAmmoFlubba:
            amount = 5.f;
            unfreeze = 10.f;
            break;

        case spaceObjects::oMiniAmmoFlubba:
            amount = 1.f;
            break;

        case spaceObjects::oAmmoBurner:
        case spaceObjects::oAmmoFlamer2:
            amount = timer::frameTime()*2.f;
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoFist:
        case spaceObjects::oAmmoROFLE:
        case spaceObjects::oAmmoRifle2:
        // case spaceObjects::oAmmoSeekers:
            unfreeze = frozen_;
            amount = life_;
            break;

        case spaceObjects::oBall:
        case spaceObjects::oShip:
        {
            if (totalLifeTime_ <= 0.5)
            {
                if (dynamic_cast<Ship*>(with) != parent_->ship())
                    amount = life_;
            }else
                amount = life_;
            break;
        }

        default:
            amount = life_ * 0.3f;
            unfreeze = 3.f;  //10;
    }

    if (frozen_ <= 0)
        life_ -= amount;
    else
    {
        frozen_ -= unfreeze;
        if (frozen_ < 0.f)
        {   frozen_ = 0.f;
            mass_ = 3.f;
            particles::spawnMultiple(2, particles::pCrushedIce, location_);
        }
    }
}
