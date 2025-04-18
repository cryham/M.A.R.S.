#include "Particles/AmmoMiniRocket.hpp"

#include "SpaceObjects/spaceObjects.hpp"
#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "Particles/particles.hpp"
#include "System/settings.hpp"
#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/ships.hpp"
#include "Shaders/postFX.hpp"
#include "Players/Player.hpp"

#include <cfloat>


std::list<AmmoMiniRocket*> AmmoMiniRocket::activeParticles_;


AmmoMiniRocket::AmmoMiniRocket(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoMiniRocket>(spaceObjects::oAmmoMiniRocket, location, 3.f, 3.0f, 10000.f)
    ,timer_(1.f)
    ,parent_(damageSource)
    ,rotation_(0.f)
    ,life_(50.f)
    ,frozen_(0.f)
    ,visible_(true)
{
    setDamageSource(damageSource);
    velocity_ = direction * 550.f;
    acceleration_ = 600.0f;

    trailEffects::attach(this, 0.05, 0.5f, 6.f, Color3f(0.1f, 0.23f, 0.35f), false);
}

AmmoMiniRocket::~AmmoMiniRocket()
{
    trailEffects::detach(this);
}


void AmmoMiniRocket::update()
{
    float const time = timer::frameTime();

    if (frozen_ <= 0)
    {
        physics::collide(this, STATICS | MOBILES);  // | PARTICLES);

        Vector2f const dir(velocity_.normalize());

        location_ += velocity_ * time;
        velocity_ += acceleration_ * dir * time;
        borders();
        // todo clamp max vel..

        particles::spawnTimed(80.f/settings::iParticleCount, particles::pFuel,
            location_ - dir*radius_ * 2.3f, dir, velocity_);
        particles::spawnTimed(5.f/settings::iParticleCount, particles::pHeatJet,
            location_ - dir*radius_ * 3.f, dir, velocity_);

        lifeTime_ += time;
        timer_ -= time;
    }
    else
    {   physics::collide(this, STATICS | MOBILES | PARTICLES);

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
        // particles::spawnMultiple(1, particles::pMiniFlame, location_);
        particles::spawnMultiple(4, particles::pHeatJet, location_);        

        // postFX::onExplosion();
        setDamageSource(parent_);
        // physics::  causeShockWave(damageSource(), location_, 150.f, 300.f, 3.f);
        // particles::spawn(particles::pShockWave, location_);
        killMe();
    }
}

//  draw
void AmmoMiniRocket::draw() const
{
    glColor4f(0.3f, 0.4f, 0.3f, 0.3f);

    Vector2f dir(velocity_.normalize()*10.f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    const Vector2f
        topL(location_ + dir + side),
        topR(location_ + dir - side),
        btmL(location_ - 3*dir + side),
        btmR(location_ - 3*dir - side);

    const int u = 0, v = 5;
    glTexCoord2f(u*0.125f,    (v+2)*0.125f); glVertex2f(topL.x_, topL.y_);
    glTexCoord2f((u+4)*0.125f,(v+2)*0.125f); glVertex2f(btmL.x_, btmL.y_);
    glTexCoord2f((u+4)*0.125f, v*0.125f);    glVertex2f(btmR.x_, btmR.y_);
    glTexCoord2f(u*0.125f,     v*0.125f);    glVertex2f(topR.x_, topR.y_);
}

void AmmoMiniRocket::onCollision(SpaceObject* with, Vector2f const& location,
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

        case spaceObjects::oAmmoFlamer2:
        case spaceObjects::oAmmoBurner:
            amount = timer::frameTime()*2.f;
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoFist:
        case spaceObjects::oAmmoROFLE:
        case spaceObjects::oAmmoMiniRocket:
            unfreeze = frozen_;
            amount = life_;
            break;

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
            amount = life_;
            unfreeze = 10;
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
