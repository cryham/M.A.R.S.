/* Turret.cpp

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

#include "SpaceObjects/Turret.hpp"

#include "SpaceObjects/physics.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "System/Color3f.hpp"
#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "Weapons/Mount.hpp"
#include "Weapons/weapons.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Players/LocalPlayer.hpp"
#include "Games/games.hpp"
#include "SpaceObjects/Ball.hpp"
#include "Shaders/postFX.hpp"
#include "defines.hpp"
#include "System/randomizer.hpp"

#include <cmath>
#include <sstream>
#include <cfloat>


Turret::Turret(Vector2f const& location, float rotation, Player* owner)
    : SpaceObject(spaceObjects::oTurret, location, settings::iShipRadius, 10.f)
    , Mount(rotation, owner)
    ,visible_(true)
    // ,ghostTimer_(1.f)
    ,frozen_(0.f)

    ,respawnTimer_(0.f)
    ,damageSourceResetTimer_(0.f)
    ,respawnLocation_(location)
    ,respawnRotation_(rotation)
    ,weapon_(NULL)
    // ,special_(NULL)
    ,life_(200.f)
    ,maxLife_(life_)

    ,damageByLocalPlayer_(0.f)
    ,damageCheckTimer_(0.f)
    ,damageDirection_(0.f, 0.f)
    ,collisionCount_(0)
{
    // color_ = Color3f::random().brightened() * 0.5f;
    color_ = Color3f(0.7,0.7,0.7) - Color3f::random() * 0.1f;
    graphic_ = randomizer::random(0, SHIP_GRAPHICS_COUNT);

	weapon_  = weapons::create(weapons::random(), this);
	// special_ = specials::create(specials::sHeal, this);  // todo

    damageSource_ = owner_;
    physics::addStaticObject(this);
}


//  update
//----------------------------------------------------------------------------------------------------------------------------------
void Turret::update()
{
    float time = timer::frameTime();

    if (damageSourceResetTimer_ > 0.f)
    {   damageSourceResetTimer_ -= time;
        if (frozen_ <= 0.f && damageSourceResetTimer_ <= 0.f)
            damageSource_ = owner_;
    }

    if (damageCheckTimer_ > 0.f)
    {   damageCheckTimer_ -= time;
        if (damageCheckTimer_ <= 0.f)
        {
            float damage(damageByLocalPlayer_*20.f);
            if (fabs(damage) >= 1.f)
            {
                particles::spawn(particles::pNumber, location_+Vector2f(0.f, -20.f),
                    Vector2f(damage, 20.f + fabs(damage)*0.02f), (damageDirection_/collisionCount_)*0.5f);
                damageDirection_ = Vector2f();
                damageByLocalPlayer_ = 0;
                collisionCount_ = 0;
            }
        }
    }

    if (visible_)
    {
        /*if (ghostTimer_ > 0.f && !(docked_ && ghostTimer_ == 1.f))
        {   ghostTimer_ -= time;
            if (ghostTimer_ <= 0.f)
                physics::addMobileObject(this);
        }*/

        if (games::elapsedTime() > settings::iCountDown || games::type() == games::gTutorial)
        {
            if (frozen_ <= 0)
            {
                //  find closest ship
                float dist = FLT_MAX;
                Ship* closest = 0;
                
                const auto& all = ships::getShips();
                for (const auto& ship : all)
                {
                    float d = (location_ - ship->location()).lengthSquare();
                    if (d < dist)
                    {   dist = d;
                        closest = ship;
                    }
                }
                if (closest)
                {   //  rotate and attack
                    auto pos = closest->location() - location_;
                    float angle = ships::GetAngle(pos.x_, -pos.y_) * 180.f/M_PI;
                #if 0
                    rotation_ = angle;
                #else
                    const float rot = settings::iTurretTurnSpeed / 100.f;
                    float diff = angle - rotation_;
                    diff = fmod(diff + 180.f,  360.f) - 180.f;

                    float amt = fabs(diff) * 5.f;
                    if (amt > 100.f)  amt = 100.f;
                    int rot_left_  = diff < 0.f ? amt : 0.f;
                    int rot_right_ = diff > 0.f ? amt : 0.f;

                    if (rot_right_ > 5)
                        fmod(rotation_+= rotateSpeed_ *time *rot * rot_right_, 360.f);
                    if (rot_left_  > 5)
                        fmod(rotation_-= rotateSpeed_ *time *rot * rot_left_, 360.f);

                    if (rot_right_ == 0 && rot_left_ == 0)
                        rotateSpeed_ = 1.0;
                    else if (rotateSpeed_ < 13.f)
                        rotateSpeed_ += time*40.f;
                #endif

                    if (weapon_ && randomizer::random(0, 1000) < settings::iTurretAttackSpeed)
                        weapon_->fire();
                }
            }else
            {
                frozen_ -= timer::frameTime()*3.f;  // melt
                life_ -= timer::frameTime()*7.f;

                if (frozen_ <= 0.f)
                {   frozen_ = 0.f;
                    mass_ = 10.f;
                    particles::spawnMultiple(2, particles::pCrushedIce, location_);
                }

                // velocity_ = Vector2f();
                if (damageSource_==players::getPlayer1() || damageSource_==players::getPlayer2() /*||
                    owner_==players::getPlayerI() || owner_==players::getPlayerII()*/)
                {
                    damageByLocalPlayer_ -= timer::frameTime()*10.f;
                    collisionCount_ = 1;
                    damageDirection_ = Vector2f(0.f, 400.f);
                    if (damageCheckTimer_ <= 0.f)
                        damageCheckTimer_ = 1.f;
                }
            }
            // check for death
            if (getLife() <= 0)  explode();
        }
    }else
    if (settings::iTurretRespawnDelay >= 0)
    {
        respawnTimer_ -= time;
        if (respawnTimer_ < 0)  respawn();
    }
}

//  draw
//----------------------------------------------------------------------------------------------------------------------------------
void Turret::draw() const
{
    if (!visible_)  return;

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0.f);

    // draw Turret
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRotatef(rotation_, 0.f, 0.f, 1.f);

    float x, y, alpha = 1.f;
    x = static_cast<float>(graphic_ % 8) * 0.125f;
    y = static_cast<float>(std::floor(graphic_ * 0.125f))*0.375f;

    glColor4f(1.f, 1.f, 1.f, alpha);
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
        glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
        glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
    glEnd();

    y += 0.125f;

    color_.gl4f(alpha);  // team-
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
        glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
        glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
    glEnd();

    y += 0.125f;

    color_.brightened().gl4f(alpha);
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
        glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
        glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
    glEnd();

    glPopMatrix();

    /*else if (respawnTimer_ > 6.f)
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0.f);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // draw glow
        owner_->team_->color().gl4f((respawnTimer_ - 6.f)*0.25f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.f, 0.75f);       glVertex2f(-radius_*3.6f,-radius_*3.6f);
            glTexCoord2f(0.f, 0.875f);      glVertex2f(-radius_*3.6f, radius_*3.6f);
            glTexCoord2f(0.125f, 0.875f);   glVertex2f( radius_*3.6f, radius_*3.6f);
            glTexCoord2f(0.125f, 0.75f);    glVertex2f( radius_*3.6f,-radius_*3.6f);
        glEnd();

        glPopMatrix();
    }*/
}

void Turret::drawWeapon() const
{
    if (!visible_)  return;

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0.f);
    glRotatef(timer::totalTime()*-50, 0.f, 0.f, 1.f);

    float alpha = 1.f;  //(ghostTimer_ == 1.f ?     0.2f*std::sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f :
        //(ghostTimer_ > 0.f ? ghostTimer_*(0.2f*std::sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f) + 1.f-ghostTimer_ : 1.f));

    // draw special
    // special_->draw(alpha * settings::iGlowAlpha / 100.f);  /// 0.7 0.2  //new

    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0.f);
    glRotatef(rotation_, 0.f, 0.f, 1.f);

    // draw weapon
    weapon_->draw(alpha);

    glPopMatrix();
}

//  Collision
//----------------------------------------------------------------------------------------------------------------------------------
void Turret::onCollision(SpaceObject* with, Vector2f const& location,
                       Vector2f const& direction, Vector2f const& velocity)
{
    if (life_ <= 0.f)
        return;

    float strength = velocity.length();
    // damage
    float amount(0.f);
    float waitForOtherDamage(0.001f);

    float unfreeze(0);

    switch (with->type())
    {
        /*case spaceObjects::oSun:
            amount = strength*0.08f + 20;
            if (strength > 50)
                sound::playSound(sound::BallPlanetCollide, location, (strength-50)/3);
            break;

        case spaceObjects::oShip:
            setDamageSource(with->damageSource());
            amount = strength * 0.01f;
            dynamic_cast<Ship*>(with)->setDamageSource(damageSource_);
            if (strength > 50)
                sound::playSound(sound::ShipCollide, location, (strength-50)/3);
            break;*/

        case spaceObjects::oShip:
        case spaceObjects::oPlanet:
        case spaceObjects::oHome:
        case spaceObjects::oSun:
            break;

        case spaceObjects::oBall:
            amount =  dynamic_cast<Ball*>(with)->heatAmount() * 0.1f;
            // particles::spawnMultiple(2, particles::pSpark, location, direction*100.f);
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            unfreeze = 10.f;
            break;


        //  clouds
        case spaceObjects::oAmmoPulse:  // ))
            amount = strength*0.002f;
            waitForOtherDamage = 0.2f;
            setDamageSource(with->damageSource());
            unfreeze = 0.1f;
        case spaceObjects::oAmmoCloud:  // OO
            amount = strength*0.004f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            unfreeze = 0.1f;
            break;

        case spaceObjects::oAmmoMinigun:  // ...
            amount = strength*0.002f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            // particles::spawnMultiple(2, particles::pSpark, location,
            //     dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.7f, velocity_, owner_->color());
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoGrenades:  // --.
            amount = strength*0.0001f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(10, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.0005f); //, owner_->color());
            unfreeze = 20.f;
            break;

        //  afk
        case spaceObjects::oAmmoAFK85:  // =
            amount = strength*0.0023f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.3f);
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoAFK47:
            amount = strength*0.003f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.3f);
            unfreeze = 0.1f;
            break;

        //  rifles  ---
        case spaceObjects::oAmmoGauss:  // --.
            amount = strength*0.0007f;
            waitForOtherDamage = 0.2f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(10, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.0005f);  //, owner_->color());
            unfreeze = 20.f;
            break;
        case spaceObjects::oAmmoLaser:  // ___
            amount = strength*0.003f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(1, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.05f);  //, owner_->color());
            unfreeze = 30.f;
            break;
        case spaceObjects::oAmmoRifle2:  // --
            amount = strength*0.006f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(20, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.5f);
            unfreeze = 20.f;
            break;
        case spaceObjects::oAmmoROFLE:
            amount = strength*0.0004f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(20, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.5f);
            unfreeze = 20.f;
            break;

        //  shotgun  <
        case spaceObjects::oAmmoShotgun2:  // <<
            amount = strength*0.0012f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.7f);
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoShotgun:
            amount = strength*0.0015f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.7f);
            unfreeze = 0.1f;
            break;

        //  freezers
        case spaceObjects::oAmmoFreezers:  // :*
            amount = randomizer::random(1.5f, 2.f) * 0.4f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            // unfreeze = 4.f;
            break;
        case spaceObjects::oAmmoLightning:  // -~
            amount = randomizer::random(0.5f, 2.f) * 0.6f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            // unfreeze = 4.f;
            break;

        //  plasma
        case spaceObjects::oAmmoPlasma:  // o
            amount = randomizer::random(5.f, 6.f);
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            unfreeze = 4.f;
            break;
        
        //  flubba  o.
        case spaceObjects::oAmmoFlubba:
            amount = randomizer::random(2.5f, 3.f);
            setDamageSource(with->damageSource());
            unfreeze = 4.f;
            break;
        case spaceObjects::oMiniAmmoFlubba:
            amount = randomizer::random(0.7f, 1.f);
            waitForOtherDamage = 0.3f;
            setDamageSource(with->damageSource());
            break;

        //  H2o
        case spaceObjects::oAmmoH2OStorm:  // *
            amount = strength*0.002f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoH2OMG:
            amount = strength*0.01f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            unfreeze = 0.1f;
            break;

        //  Flame  ~~
        case spaceObjects::oAmmoFlamer2:
        case spaceObjects::oAmmoBurner:
            amount = timer::frameTime();
            waitForOtherDamage = 0.15f;
            // if (frozen_ <= 0)
            //     velocity_ += velocity*0.03f*timer::frameTime();
            // chance to spawn smoke
            if (randomizer::random(0.f, 100.f) / settings::iParticleCount < 0.01f)
                particles::spawn(particles::pSmoke, location, velocity);
            setDamageSource(with->damageSource());
            unfreeze = 0.05f;
            break;

        //  rockets  - =
        case spaceObjects::oAmmoSeekers:
            amount = 3.f;
            setDamageSource(with->damageSource());
            unfreeze = 5.f;
            break;
        case spaceObjects::oAmmoMiniRocket:
            amount = 20.f;
            setDamageSource(with->damageSource());
            unfreeze = 10.f;
            break;
        case spaceObjects::oAmmoRocket:
            amount = 10.f;
            setDamageSource(with->damageSource());
            unfreeze = 10.f;
            break;


        //  big  -o
        case spaceObjects::oAmmoFist:
            amount = 25.f+randomizer::random(-3.f, 3.f);
            setDamageSource(with->damageSource());
            unfreeze = 15.f;
            break;

        case spaceObjects::oAmmoInsta:
            amount = life_ / 8.f;
            setDamageSource(with->damageSource());
            break;

        case spaceObjects::oCannonBall:
            amount = life_;
            setDamageSource(owner_);
            unfreeze = frozen_;
            break;

        default:;
    }

    if (frozen_ > 0)
    {   frozen_ -= unfreeze;

        if (frozen_ <= 0.f)
        {   frozen_ = 0.f;

            mass_ = 10.f;
            particles::spawnMultiple(2, particles::pCrushedIce, location_);
        }
    }

    amount *= settings::iDamageScale / 100.f;

    if (attackable() && life_ > 0.f)
    {
        // increase the amount done to weak bots
        // strong bots just take normal damage
        // if (damageSource_ &&
        //     (damageSource_->controlType_ == controllers::cPlayer1 ||
        //      damageSource_->controlType_ == controllers::cPlayer2) /*&&
        //     (owner_->controlType_ != controllers::cPlayer1 &&
        //      owner_->controlType_ != controllers::cPlayer2)*/ &&
        //     amount < life_)
        // {
        //     amount *= (10.f - 0.09f*settings::iBotsDifficulty);
        // }

        if ((damageSource_ &&
            (damageSource_->controlType_ == controllers::cPlayer1 ||
             damageSource_->controlType_ == controllers::cPlayer2))/* ||
            owner_->controlType_ == controllers::cPlayer1 ||
            owner_->controlType_ == controllers::cPlayer2*/)
        {
            Vector2f direction;

            MobileSpaceObject* target = dynamic_cast<MobileSpaceObject*>(with);
            if (target)
                direction = target->velocity();

            drainLife(damageSource_, amount, direction, waitForOtherDamage);
        }else
            life_ -= amount;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------

void Turret::onShockWave(Player* damageSource, float intensity)
{
    if (frozen_ > 0)
        frozen_ -= 10;
    else
    {
        setDamageSource(damageSource);

        float damage(intensity * 0.1f * (20.f + settings::iBotsDifficulty));
        life_ -= damage;
        if (damageSource_ && (damageSource_->controlType_ == controllers::cPlayer1 ||
                              damageSource_->controlType_ == controllers::cPlayer2))
        {
            damageByLocalPlayer_ -= damage;
            ++collisionCount_;
            if (damageCheckTimer_ <= 0.f)
                damageCheckTimer_ = 0.01f;
        }
    }
}

void Turret::setDamageSource(Player* evilOne)
{
    if (frozen_ <= 0.f)
    {
        damageSource_ = evilOne;
        damageSourceResetTimer_ = 1.8f;
    }
}

void Turret::drainLife(Player* source, float amount, Vector2f const& direction, float waitForOtherDamage)
{
    if (dynamic_cast<LocalPlayer*>(source) != NULL /*|| dynamic_cast<LocalPlayer*>(owner_) != NULL*/)
    {
        if (damageCheckTimer_ <= 0.f)
            damageCheckTimer_ = waitForOtherDamage;
        damageByLocalPlayer_ -= amount;

        damageDirection_ += direction;

        ++collisionCount_;
    }
    setDamageSource(source);
    life_ -= amount;
}

void Turret::heal(Player* source, int amount)
{
    float lifeAmount(maxLife_ / 100.f * amount);
    if (life_ + lifeAmount > maxLife_)
        lifeAmount = maxLife_ - life_;
    life_ += lifeAmount;

    if (source->controlType_ == controllers::cPlayer1 || source->controlType_ == controllers::cPlayer2)
    {
        damageByLocalPlayer_ += lifeAmount;
        ++collisionCount_;
        if (damageCheckTimer_ <= 0.f)
            damageCheckTimer_ = 0.01f;
    }
}

float Turret::getLife() const
{
    return life_ < 0.f ? 0.f : life_/maxLife_*100.f;
}

//  explode
void Turret::explode()
{
    sound::playSound(sound::ShipExplode, location_, 100.f);
    particles::spawnMultiple(5 , particles::pFragment, location_, location_, location_);
    particles::spawnMultiple(50, particles::pDust, location_);
    particles::spawnMultiple(20, particles::pExplode, location_);
    particles::spawnMultiple(5, particles::pBurningFragment, location_);
    particles::spawnMultiple(1, particles::pMiniFlame, location_);
    physics::  causeShockWave(damageSource(), location_, 400.f, 200.f, 2.f);
    particles::spawn(particles::pShockWave, location_);
    // physics::  removeMobileObject(this);
    timer::    onShipExplode();
    postFX::   onExplosion();

    visible_ = false;
    life_ = 0.f;
    respawnTimer_ = settings::iTurretRespawnDelay / 10.f;

    frozen_ = 0.f;
    // special_->stop();

    // if (!damageSource_)
    //     damageSource_ = owner_;

    /*if (damageSource_ == owner_)
    {
        ++owner_->suicides_;
        --owner_->points_;
        if (games::type() != games::gSpaceBall && games::type() != games::gCannonKeep)
            damageSource_->team()->subtractPoint();

        announcer::announce(announcer::Affronting);
    }
    else if (damageSource_->team() == owner_->team())
    {
        ++damageSource_->teamKills_;
        --damageSource_->points_;

        // (damageSource_->Ship()->fragStars_-1 < 0) ? damageSource_->Ship()->fragStars_=0 : --damageSource_->Ship()->fragStars_;

        if (games::type() != games::gSpaceBall && games::type() != games::gCannonKeep)
            damageSource_->team()->subtractPoint();

        announcer::announce(announcer::Affronting);
    }
    else
    {   ++damageSource_->frags_;
        ++damageSource_->points_;

        if (games::type() != games::gSpaceBall && games::type() != games::gCannonKeep)
            damageSource_->team()->addPoint();

        ++damageSource_->Turret()->fragStars_;

        announcer::announce(announcer::Praising);
    }*/
}

void Turret::respawn()
{
    location_ = respawnLocation_;
    rotation_ = respawnRotation_;
    rotateSpeed_ = 1.f;
    life_ = maxLife_;

    // fragStars_ = 0;
    visible_ = true;
    damageByLocalPlayer_ = 0.f;
    damageDirection_ = Vector2f();
    collisionCount_ = 0;

    sound::playSound(sound::ShipRespawn, location_, 100.f);
}


bool Turret::collidable() const
{
    return visible_; // && ghostTimer_ <= 0.f;
}

bool Turret::attackable() const
{
    return collidable() && frozen_ <= 0;
}
