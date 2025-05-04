#include "SpaceObjects/Ship.hpp"

#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"
#include "Games/games.hpp"
#include "SpaceObjects/Ball.hpp"
#include "Items/items.hpp"
#include "SpaceObjects/Home.hpp"
#include "System/randomizer.hpp"
#include "System/window.hpp"

#include <cmath>
#include <math.h>
#include <sstream>
using namespace std;


//  update
//----------------------------------------------------------------------------------------------------------------------------------
void Ship::update()
{
    float time = timer::frameTime();

    if (weaponChangeTime_ > 0.f)
        weaponChangeTime_ -= time;

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
                particles::spawn(particles::pNumber, location_ + Vector2f(0.f, -20.f),
                    Vector2f(damage, 20.f + fabs(damage) * 0.02f),
                    (damageDirection_ / collisionCount_ + velocity_) * 0.5f);
                
                damageDirection_ = Vector2f();
                damageByLocalPlayer_ = 0;
                collisionCount_ = 0;
            }
        }
    }

    if (visible_)
    {
        if (ghostTimer_ > 0.f && !(docked_ && ghostTimer_ == 1.f))
        {   ghostTimer_ -= time;
            if (ghostTimer_ <= 0.f)
                physics::addMobileObject(this);
        }
        const float chill = 1.f - chilled_;

        if (games::elapsedTime() > settings::iCountDown || games::type() == games::gTutorial)
        {
            const float par = settings::iParticleCount;
            if (frozen_ <= 0)
            {
                const float rot = settings::iShipTurnSpeed / 100.f;  /// 0.25f; //0.3f;  //new
                float angleRad = rotation_ * M_PI / 180.f;

                Vector2f dir( cos(angleRad), sin(angleRad));
                Vector2f dirBack( cos(angleRad + M_PI), sin(angleRad + M_PI));
                Vector2f dirRight(cos(angleRad + M_PI_2), sin(angleRad + M_PI_2));
                Vector2f dirLeft( cos(angleRad - M_PI_2), sin(angleRad - M_PI_2));

                Vector2f acceleration;
                float slower = collectedPowerUps_[items::puReverse] ? 0.33f : 1.f;
                float boostMul = 1.f + boost_ / 100.f;

                //  mouse turn  ------------  new
                if (owner_->controlType_ == controllers::cPlayer1 && settings::bPlayer1mouseAim ||
                    owner_->controlType_ == controllers::cPlayer2 && settings::bPlayer2mouseAim)
                {
                    //  get angle to mouse pointer
                    Vector2f mp = window::getMousePosition(), ws = window::getWindowSize();
                    float sx = location_.x_ / settings::iMapXsize * ws.x_;
                    float sy = location_.y_ / settings::iMapYsize * ws.y_;
                    float angle = ships::GetAngle(mp.x_ - sx, -mp.y_ + sy) * 180.f/M_PI;
                    // cout << " shp: " << location_.x_ << " " << location_.y_
                    //     << " m " << p.x_ << " " << p.y_ << " rot " << rotation_ //* 180.f/M_PI
                    //     << " a " << a * 180.f/M_PI << endl;
                    
                #if 0  // immediate-
                    rotation_ = angle;
                #else
                    float diff = angle - rotation_;
                    // cout << "ang  " << angle << "  rot " << rotation_ << "  dif " << diff << endl;
                    while (diff > 180.f)  diff -= 360.f;
                    while (diff <-180.f)  diff += 360.f;
                    // diff = fmod(diff + 180.f,  360.f) - 180.f;

                    float amt = min(100.f, fabs(diff) * 5.f);
                    // cout << "  mod " << diff << "  amt " << amt << endl;
                    float rot_left_  = diff < 0.f ? amt : 0.f;
                    float rot_right_ = diff > 0.f ? amt : 0.f;

                    // if (rot_right_ > 5)
                        rotation_+= rotateSpeed_ *time *rot *slower * rot_right_;
                    // if (rot_left_  > 5)
                        rotation_-= rotateSpeed_ *time *rot *slower * rot_left_;
                    
                    if (rot_right_ == 0 && rot_left_ == 0)
                        rotateSpeed_ = 1.0;
                    else if (rotateSpeed_ < 13.f)
                        rotateSpeed_ += time*40.f;

                    rotation_ = fmodf(rotation_, 360.f);  // always 0..360
                    while (rotation_ < 0.f)  rotation_ += 360.f;
                #endif

                    //  accelerate sideways
                    if (right_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.01f * right_;
                        float amt = right_ * boostMul;
                        acceleration = dirRight * 5.f * amt;
                        particles::spawnTimed(1.5f / par * amt, particles::pFuel,
                            location_ - dirRight*radius_, dirRight, velocity_);
                        particles::spawnTimed(0.1f / par * amt, particles::pHeatJet,
                            location_ - dirRight*radius_*1.5f, dirRight, velocity_);
                    }else
                    if (left_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.01f * left_;
                        float amt = left_ * boostMul;
                        acceleration = dirLeft * 5.f * amt;
                        particles::spawnTimed(1.5f / par * amt, particles::pFuel,
                            location_ - dirLeft*radius_, dirLeft, velocity_);
                        particles::spawnTimed(0.1f / par * amt, particles::pHeatJet,
                            location_ - dirLeft*radius_*1.5f, dirLeft, velocity_);
                    }

                    //  accelerate
                    if (up_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.005f * up_;
                        float amt = up_ * boostMul;
                        acceleration = dir * 5.f * amt;
                        particles::spawnTimed(1.5f / par * amt, particles::pFuel,
                            location_ - dir*radius_, dir, velocity_);
                        particles::spawnTimed(0.1f / par * amt, particles::pHeatJet,
                            location_ - dir*radius_*1.5f, dir, velocity_);
                    }else
                    if (down_ > 5 && getFuel() > 0.f)
                    {   // backward
                        fuel_ -= time*0.005f * down_;
                        float amt = down_ * boostMul;
                        acceleration = dir * -3.f * amt;
                        particles::spawnTimed(1.5f / par * amt, particles::pFuel,
                            location_ - dirBack*radius_, dirBack, velocity_);
                        particles::spawnTimed(0.1f / par * amt, particles::pHeatJet,
                            location_ - dirBack*radius_*1.5f, dirBack, velocity_);
                    }
                }
                else    // turn by keys  ------------
                if (boost_ > 15)
                {
                    //  boost accelerate
                    if (up_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.03f * up_;
                        acceleration = dir * 10.f * up_ * boost_ / 100.f * slower;
                        particles::spawnTimed(1.5f / par * up_, particles::pFuel,
                            location_ - dir*radius_, dir, velocity_);
                        particles::spawnTimed(0.1f / par * up_, particles::pHeatJet,
                            location_ - dir*radius_*1.5f, dir, velocity_);
                    }else
                    if (down_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.02f * down_;
                        acceleration = dir * -7.f * down_  * boost_ / 100.f * slower;
                        particles::spawnTimed(1.5f / par * down_, particles::pFuel,
                            location_ - dir*radius_, dir, velocity_);
                        particles::spawnTimed(0.1f / par * down_, particles::pHeatJet,
                            location_ - dir*radius_*1.5f, dir, velocity_);
                    }

                    //  accelerate sideways
                    if (right_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.02f * right_;  // * 10.f
                        acceleration = dirRight * 5.f * right_ * boost_ / 100.f;
                        particles::spawnTimed(1.5f / par * right_, particles::pFuel,
                            location_ - dirRight*radius_, dirRight, velocity_);
                        particles::spawnTimed(0.1f / par * right_, particles::pHeatJet,
                            location_ - dirRight*radius_*1.5f, dirRight, velocity_);
                    }else
                    if (left_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.02f * left_;
                        acceleration = dirLeft * 5.f * left_ * boost_ / 100.f;
                        particles::spawnTimed(1.5f / par * left_, particles::pFuel,
                            location_ - dirLeft*radius_, dirLeft, velocity_);
                        particles::spawnTimed(0.1f / par * left_, particles::pHeatJet,
                            location_ - dirLeft*radius_*1.5f, dirLeft, velocity_);
                    }
                }else
                {
                    //  turn manual
                    if (right_ > 5)
                        fmod(rotation_+= chill * rotateSpeed_ *time *rot *slower * right_, 360.f);
                    if (left_  > 5)
                        fmod(rotation_-= chill * rotateSpeed_ *time *rot *slower * left_, 360.f);

                    if (right_ == 0 && left_ == 0)
                        rotateSpeed_ = 1.0;
                    else if (rotateSpeed_ < 13.f)
                        rotateSpeed_ += time*40.f;

                    //  accelerate
                    if (up_ > 5 && getFuel() > 0.f)
                    {   fuel_ -= time*0.005f * up_;
                        acceleration = dir * 5.f * up_;
                        particles::spawnTimed(1.5f / par * up_, particles::pFuel,
                            location_-dir*radius_, dir, velocity_);
                        particles::spawnTimed(0.1f / par * up_, particles::pHeatJet,
                            location_-dir*radius_*1.5f, dir, velocity_);
                    }else
                    if (down_ > 5 && getFuel() > 0.f)
                    {   // backward
                        fuel_ -= time*0.005f * down_;
                        acceleration = dir * -3.f * down_;
                        particles::spawnTimed(1.5f / par * down_, particles::pFuel,
                            location_ - dir*radius_, dir, velocity_);
                        particles::spawnTimed(0.1f / par * down_, particles::pHeatJet,
                            location_ - dir*radius_*1.5f, dir, velocity_);
                    }
                }
                fuel_ += time * settings::iFuelRegen / 100.f;  /// 0.5  //new
                if (fuel_ > maxFuel_)
                    fuel_ = maxFuel_;

                // movement
                // check if docked
                Home const* home = owner_->team()->home();
                Vector2f toHome = home->location() - location_;
                bool closeToHome(toHome.lengthSquare() < pow(home->radius() + radius_ + 0.1f, 2.f));

                if (up_ < 10 && velocity_.lengthSquare() < 13000.f &&
                    closeToHome && ((dir + toHome.normalize()).lengthSquare() < 0.26f))
                {
                    docked_ = true;
                    velocity_ = Vector2f();
                    if (fuel_ < maxFuel_)
                    {
                        if (fuel_ > 0)
                            fuel_ += time*maxFuel_*0.2;
                    }
                    else fuel_ = maxFuel_;

                    if (life_ < maxLife_)
                    {
                        if (life_ > 0)
                            life_ += time*maxLife_*0.2;
                    }
                    else life_ = maxLife_;

                    if (owner_->controlType_ == controllers::cPlayer1 ||
                        owner_->controlType_ == controllers::cPlayer2)
                    {
                        if (life_ < maxLife_)
                        {
                            damageByLocalPlayer_ += time*maxLife_*0.2;
                            collisionCount_ = 1;
                            damageDirection_ = Vector2f(0.f, -250.f);
                        }
                        if (damageCheckTimer_ <= 0.f)
                            damageCheckTimer_ = 0.6f;
                    }
                }else
                {
                    if (settings::iRegeneration > 0)  /// 0.06 life regeneration  //new
                    {
                        life_ += time * maxLife_ * settings::iRegeneration / 1000.f;
                        if (life_ > maxLife_)
                            life_ = maxLife_;
                    }
                    docked_ = false;
                    weaponChange_ = false;
                    specialChange_ = false;
                    acceleration += physics::attract(this);
                }

                //  move  ----
                // s += v*t + 0.5*a*t^2  v += a*t
                location_ += chill * (velocity_*time + acceleration*0.5f*time*time);
                velocity_ += chill * (acceleration*time + velocity_*-0.2f*time);


                //  new status
                //  chilled  slow down  ***
                chilled_ -= time * 0.3f;  // fade out
                if (chilled_ > 0.9f)  chilled_ = 0.9f;  // max
                if (chilled_ < 0.f)   chilled_ = 0.f;

                //  shocked_  fade  ***
                shocked_ -= time * 0.3f;
                if (shocked_ > 0.9f)  shocked_ = 0.9f;  // max
                if (shocked_ < 0.f)   shocked_ = 0.f;


                if (ghostTimer_ <= 0.f)
                    physics::collide(this, STATICS | MOBILES);
                else
                    physics::collide(this, STATICS);

                borders();
                if (!settings::bCyclicBorderX)
                {
                    if (location_.x_ < radius_)
                    {   location_.x_ = radius_;
                        velocity_.x_ = 0.f;
                    }
                    if (location_.x_ > settings::iMapXsize - radius_)
                    {   location_.x_ = settings::iMapXsize - radius_;
                        velocity_.x_ = 0.f;
                    }
                }
                if (!settings::bCyclicBorderY)
                {
                    if (location_.y_ < radius_)
                    {   location_.y_ = radius_;
                        velocity_.y_ = 0.f;
                    }
                    if (location_.y_ > settings::iMapYsize - radius_)
                    {   location_.y_ = settings::iMapYsize - radius_;
                        velocity_.y_ = 0.f;
                    }
                }
            }else
            {
                frozen_ -= timer::frameTime()*3.f;
                life_ -= timer::frameTime()*7.f;

                if (frozen_ <= 0.f)
                {   frozen_ = 0.f;
                    mass_ = 10.f;
                    particles::spawnMultiple(2, particles::pCrushedIce, location_);
                }

                velocity_ = Vector2f();
                if (damageSource_==players::getPlayer1() || damageSource_==players::getPlayer2() ||
                    owner_==players::getPlayer1() || owner_==players::getPlayer2())
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
    {
        respawnTimer_ -= time;
        if (respawnTimer_ < 0)  respawn();
    }
}


//  Collision
//----------------------------------------------------------------------------------------------------------------------------------
void Ship::onCollision(SpaceObject* with, Vector2f const& location,
                       Vector2f const& direction, Vector2f const& velocity)
{
    float strength = velocity.length();
    // damage
    float amount(0.f);
    float waitForOtherDamage(0.001f);

    float unfreeze(0);

    switch (with->type())
    {
        case spaceObjects::oSun:
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
            break;

        case spaceObjects::oPlanet:
            if (strength > 75)
                amount = strength*0.04f;  // 0.08
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            break;

        case spaceObjects::oHome:
            if (strength > 150)
                amount = strength*0.06f;
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            break;

        case spaceObjects::oBall:
            amount = dynamic_cast<Ball*>(with)->heatAmount() * 0.1f;
            particles::spawnMultiple(2, particles::pSpark, location, direction*100.f, velocity_, owner_->color());
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            unfreeze = 10.f;
            break;


        //  freezers
        case spaceObjects::oChill:  // .. is particle, won't work ..
            amount = randomizer::random(1.5f, 2.f) * 0.25f;
            chilled_ += amount * 0.04f;  // 0.1  * timer::frameTime() ?
            break;
        case spaceObjects::oAmmoFreezers:  // :*
            amount = randomizer::random(1.5f, 2.f) * 0.25f  *0.3f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            chilled_ += amount * 0.10f;  // 0.15
            break;
        case spaceObjects::oAmmoLightning:  // -~
            amount = randomizer::random(0.5f, 2.f) * 0.35f  *0.3f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            shocked_ += amount * 0.08f;  // 0.1
            break;

        //  clouds
        case spaceObjects::oAmmoPulse:  // ))
            // amount = strength*0.0001f;
            amount = 1.2f;
            waitForOtherDamage = 0.2f;
            setDamageSource(with->damageSource());
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoCloud:  // OO
            amount = strength*0.001f  *0.5f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            chilled_ += amount * 0.04f;
            shocked_ += amount * 0.03f;  // 0.1
            unfreeze = 0.1f;
            break;

        case spaceObjects::oAmmoMinigun:  // ...
            amount = strength*0.001f;
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
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.0005f, velocity_*0.001f, owner_->color());
            unfreeze = 20.f;
            break;

        //  afk
        case spaceObjects::oAmmoAFK85:  // =
            amount = strength*0.0023f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.3f, velocity_, owner_->color());
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoAFK47:
            amount = strength*0.003f;
            waitForOtherDamage = 0.15f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.3f, velocity_, owner_->color());
            unfreeze = 0.1f;
            break;

        //  rifles  ---
        case spaceObjects::oAmmoGauss:  // --.
            amount = strength*0.0007f;
            waitForOtherDamage = 0.2f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(10, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.0005f, velocity_*0.001f, owner_->color());
            unfreeze = 20.f;
            break;
        case spaceObjects::oAmmoLaser:  // ___
            amount = strength*0.003f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(1, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.05f, velocity_, owner_->color());
            unfreeze = 30.f;
            break;
        case spaceObjects::oAmmoRifle2:  // --
            amount = strength*0.006f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(20, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.05f, velocity_, owner_->color());
            unfreeze = 20.f;
            break;
        case spaceObjects::oAmmoROFLE:
            amount = strength*0.0004f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(20, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.5f, velocity_, owner_->color());
            unfreeze = 20.f;
            break;

        //  shotgun  <
        case spaceObjects::oAmmoShotgun2:  // <<
            amount = strength*0.0007f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.7f, velocity_, owner_->color());
            unfreeze = 0.1f;
            break;
        case spaceObjects::oAmmoShotgun:
            amount = strength*0.0015f;
            waitForOtherDamage = 0.1f;
            setDamageSource(with->damageSource());
            particles::spawnMultiple(2, particles::pSpark, location,
                dynamic_cast<MobileSpaceObject*>(with)->velocity() * 0.7f, velocity_, owner_->color());
            unfreeze = 0.1f;
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
            if (frozen_ <= 0)
                velocity_ += velocity*0.03f * timer::frameTime();
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

    amount *= settings::iDamageScale / 100.f;  /// 0.5f;  //new

    if (attackable())
    {
        // increase the amount done to weak bots
        // strong bots just take normal damage
        if (damageSource_ &&
            (damageSource_->controlType_ == controllers::cPlayer1 ||
             damageSource_->controlType_ == controllers::cPlayer2) &&
            (owner_->controlType_ != controllers::cPlayer1 &&
             owner_->controlType_ != controllers::cPlayer2) &&
            amount < life_)
        {
            amount *= (10.f - 0.09f*settings::iBotsDifficulty);
        }

        if ((damageSource_ &&
            (damageSource_->controlType_ == controllers::cPlayer1 ||
             damageSource_->controlType_ == controllers::cPlayer2)) ||
            owner_->controlType_ == controllers::cPlayer1 ||
            owner_->controlType_ == controllers::cPlayer2)
        {
            Vector2f direction;

            MobileSpaceObject* target = dynamic_cast<MobileSpaceObject*>(with);
            if (target)
                direction = target->velocity();

            drainLife(damageSource_, amount, direction, waitForOtherDamage);
        }
        else
            life_ -= amount;
    }
}
