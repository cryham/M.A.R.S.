#include "SpaceObjects/Ship.hpp"

#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "Weapons/weapons.hpp"
#include "Weapons/Mount.hpp"
#include "Specials/specials.hpp"
#include "Media/sound.hpp"
#include "Hud/hud.hpp"
#include "Media/text.hpp"
#include "Players/Player.hpp"
#include "Players/LocalPlayer.hpp"
#include "Teams/Team.hpp"
#include "Games/games.hpp"
#include "Controllers/Controller.hpp"
#include "SpaceObjects/Ball.hpp"
#include "Media/announcer.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "Shaders/postFX.hpp"
#include "Items/items.hpp"
#include "SpaceObjects/Home.hpp"
#include "defines.hpp"
#include "System/randomizer.hpp"
#include "System/window.hpp"

#include <cmath>
#include <sstream>
using namespace std;


Ship::Ship(Vector2f const& location, float rotation, Player* owner)
    : MobileSpaceObject(spaceObjects::oShip, location, settings::iShipRadius, 10.f)
    , Mount(0.f, owner)
    ,weaponChangeTime_(0.f)
    ,owner_(owner)
    ,up_(0), down_(0), left_(0), right_(0), boost_(0)
    ,docked_(true)
    ,weaponChange_(true)
    ,specialChange_(false)
    ,visible_(true)
    ,ghostTimer_(1.f)
    ,frozen_(0.f)
    ,respawnTimer_(0.f)
    ,damageSourceResetTimer_(0.f)
    ,respawnLocation_(location)
    ,respawnRotation_(rotation)
    ,life_(200.f)
    ,maxLife_(life_)
    ,fuel_(100.f)
    ,maxFuel_(fuel_)
    ,collectedPowerUps_(items::COUNT, nullptr)
    ,fragStars_(0)
    ,damageByLocalPlayer_(0.f)
    ,damageCheckTimer_(0.f)
    ,damageDirection_(0.f, 0.f)
    ,collisionCount_(0)
{
    if (owner_->controlType_ == controllers::cPlayer1)
    {
        decoObjects::addHighlight(this);
        weapon_  = weapons:: create(settings::player1Weapon, this);
        special_ = specials::create(settings::player1Special, this);
        decoObjects::addName(this, false);
    }
    else if (owner_->controlType_ == controllers::cPlayer2)
    {
        decoObjects::addHighlight(this);
        weapon_  = weapons:: create(settings::player2Weapon, this);
        special_ = specials::create(settings::player2Special, this);
        decoObjects::addName(this, false);
    }
    else
    {   weapon_  = weapons:: create(weapons::random(), this);
        special_ = specials::create(specials::sHeal, this);
        decoObjects::addName(this, true);  // settings::bBotBars
    }
    owner->ship_ = this;
    damageSource_ = owner_;
}


//  draw
//----------------------------------------------------------------------------------------------------------------------------------
void Ship::draw() const
{
    if (visible_)
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0.f);

        // draw ship
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glRotatef(rotation_, 0.f, 0.f, 1.f);

        float x, y, alpha(ghostTimer_ == 1.f ? 0.2f * sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f : 
            (ghostTimer_ > 0.f ? ghostTimer_* (0.2f * sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f) + 1.f-ghostTimer_ : 1.f));

        x = static_cast<float>(owner_->graphic()%8)*0.125f;
        y = static_cast<float>(floor(owner_->graphic()*0.125f))*0.375f;

        glColor4f(1.f, 1.f, 1.f, alpha);
        glBegin(GL_QUADS);
            glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
            glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
            glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
            glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
        glEnd();

        y += 0.125f;

        owner_->team()->color().gl4f(alpha);
        glBegin(GL_QUADS);
            glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
            glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
            glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
            glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
        glEnd();

        y += 0.125f;

        owner_->color().gl4f(alpha);
        glBegin(GL_QUADS);
            glTexCoord2f(x, y+0.125f);          glVertex2f(-radius_, -radius_);
            glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-radius_,  radius_);
            glTexCoord2f(x+0.125f, y);          glVertex2f( radius_,  radius_);
            glTexCoord2f(x, y);                 glVertex2f( radius_, -radius_);
        glEnd();

        glPopMatrix();
    }
    else if (respawnTimer_ > 6.f)
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
    }
}

void Ship::drawWeapon() const
{
     if (visible_)
     {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0.f);
        glRotatef(timer::totalTime()*-50, 0.f, 0.f, 1.f);

        float alpha(ghostTimer_ == 1.f ?      0.2f * sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f :
            (ghostTimer_ > 0.f ? ghostTimer_*(0.2f * sin(timer::totalTime()*8.f + 1.5f*M_PI)+0.4f) + 1.f-ghostTimer_ : 1.f));

        // draw special
        special_->draw(alpha * settings::iGlowAlpha / 100.f);  /// 0.7 0.2  //new

        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0.f);
        glRotatef(rotation_, 0.f, 0.f, 1.f);

        // draw weapon
        weapon_->draw(alpha);

        glPopMatrix();
     }
}
//----------------------------------------------------------------------------------------------------------------------------------

void Ship::onShockWave(Player* damageSource, float intensity)
{
    if (frozen_ > 0)
        frozen_ -= 10;
    else
    {
        setDamageSource(damageSource);
        if (!collectedPowerUps_[items::puShield])
        {
            float damage(intensity*0.1f*(20.f + settings::iBotsDifficulty));
            life_ -= damage;
            if ((damageSource_ &&
                (damageSource_->controlType_ == controllers::cPlayer1 ||
                 damageSource_->controlType_ == controllers::cPlayer2)) ||
                owner_->controlType_ == controllers::cPlayer1 ||
                owner_->controlType_ == controllers::cPlayer2)
            {
                damageByLocalPlayer_ -= damage;
                ++collisionCount_;
                if (damageCheckTimer_ <= 0.f)
                    damageCheckTimer_ = 0.01f;
            }
        }
    }
}

void Ship::setDamageSource(Player* evilOne)
{
    if (frozen_ <= 0.f)
    {
        damageSource_ = evilOne;
        damageSourceResetTimer_ = 1.8f;
    }
}

void Ship::drainLife(Player* source, float amount, Vector2f const& direction, float waitForOtherDamage)
{
    if (dynamic_cast<LocalPlayer*>(source) ||
        dynamic_cast<LocalPlayer*>(owner_))
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

void Ship::heal(Player* source, int amount)
{
    float lifeAmount((maxLife_/100.f)*amount);
    if (life_ + lifeAmount > maxLife_)
        lifeAmount = maxLife_-life_;
    life_ += lifeAmount;

    if (source->controlType_ == controllers::cPlayer1 ||
        source->controlType_ == controllers::cPlayer2 ||
        owner_->controlType_ == controllers::cPlayer1 ||
        owner_->controlType_ == controllers::cPlayer2)
    {
        damageByLocalPlayer_ += lifeAmount;
        ++collisionCount_;
        if (damageCheckTimer_ <= 0.f)
            damageCheckTimer_ = 0.01f;
    }
}

void Ship::refuel(Player* source, int amount)
{
    float fuelAmount(maxFuel_/100.f * amount);
    (fuel_ + fuelAmount) > maxFuel_ ? fuel_ = maxFuel_ : fuel_ += fuelAmount;
}

float Ship::getLife() const
{
    return life_ < 0.f ? 0.f : life_/maxLife_*100.f;
}

float Ship::getFuel() const
{
    return fuel_ < 0.f ? 0.f : fuel_/maxFuel_*100.f;
}

Player* Ship::getOwner() const
{
    return owner_;
}

vector<PowerUp*> const& Ship::getCollectedPowerUps() const
{
    return collectedPowerUps_;
}


void Ship::WeaponNext()
{
    delete weapon_;
    weaponChangeTime_ = 1.f;
    auto next = weapons::getNext(weapon_->getType(), true, 1);
    weapon_ = weapons::create(next, this);
}
void Ship::WeaponPrev()
{
    delete weapon_;
    weaponChangeTime_ = 1.f;
    auto next = weapons::getNext(weapon_->getType(), true, -1);
    weapon_ = weapons::create(next, this);
}

//  explode
//----------------------------------------------------------------------------------------------------------------------------------
void Ship::explode()
{
    sound::playSound(sound::ShipExplode, location_, 100.f);
    particles::spawnMultiple(5 , particles::pFragment, location_, location_, location_, owner_->color());
    particles::spawnMultiple(50, particles::pDust, location_);
    particles::spawnMultiple(20, particles::pExplode, location_);
    particles::spawnMultiple(5, particles::pBurningFragment, location_);
    particles::spawnMultiple(1, particles::pMiniFlame, location_);
    physics::  causeShockWave(damageSource(), location_, 400.f, 200.f, 2.f);
    particles::spawn(particles::pShockWave, location_);
    physics::  removeMobileObject(this);
    timer::    onShipExplode();
    postFX::   onExplosion();
    
    visible_ = false;
    life_ = 0.f;
    fuel_ = 0.f;

    respawnTimer_ = settings::iRespawnDelay / 10.f;  /// 2.f;  //new
    
    frozen_ = 0.f;
    special_->stop();

    ++owner_->deaths_;

    if (!damageSource_)
        damageSource_ = owner_;

    if (damageSource_ == owner_)
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

        if (damageSource_->ship()->fragStars_-1 < 0)
            damageSource_->ship()->fragStars_ = 0;
        else
            --damageSource_->ship()->fragStars_;

        if (games::type() != games::gSpaceBall && games::type() != games::gCannonKeep)
            damageSource_->team()->subtractPoint();

        announcer::announce(announcer::Affronting);
    }
    else
    {
        ++damageSource_->frags_;
        ++damageSource_->points_;

        if (games::type() != games::gSpaceBall && games::type() != games::gCannonKeep)
            damageSource_->team()->addPoint();

        ++damageSource_->ship()->fragStars_;

        announcer::announce(announcer::Praising);
    }
}

void Ship::respawn()
{
    location_ = respawnLocation_;
    rotation_ = respawnRotation_;
    velocity_ = Vector2f();
    rotateSpeed_ = 1.f;
    life_ = maxLife_;
    fuel_ = maxFuel_;
    fragStars_ = 0;
    ghostTimer_ = 1.f;
    visible_ = true;
    docked_ = true;
    damageByLocalPlayer_ = 0.f;
    damageDirection_ = Vector2f();
    collisionCount_ = 0;
    sound::playSound(sound::ShipRespawn, location_, 100.f);
}


bool Ship::collidable() const
{
    return visible_ && ghostTimer_ <= 0.f;
}

bool Ship::attackable() const
{
    return collidable() && frozen_ <= 0 && !collectedPowerUps_[items::puShield];
}
