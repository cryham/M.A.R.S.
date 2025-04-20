#include "SpaceObjects/Asteroid.hpp"

#include "Media/texture.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "System/Vector2f.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Media/sound.hpp"
#include "Particles/particles.hpp"
#include "Shaders/postFX.hpp"
#include "Players/Player.hpp"
#include "System/randomizer.hpp"

#include <cmath>


Asteroid::Asteroid(Vector2f const& location, float radius, int type)
    :MobileSpaceObject(spaceObjects::oAsteroid, location, radius, radius * 2.f)
    ,rotation_(0)
    ,rotateSpeed_(randomizer::random(-0.3f, 0.4f))
    ,frozen_(0.f)
    ,sticky_(true)
    ,visible_(true)
    ,respawnLocation_(location)
    ,respawnRotation_(0)
    ,heatTimer_(0.f)
    ,smokeTimer_(0.f)
    ,respawnTimer_(0.f)
{
    physics::addMobileObject(this);
    color_ = Color3f(1.f,1.f,1.f) - color_.random() * 0.01f * settings::iAsteroidsColors;
    type_ = std::min(type, ASTEROIDS_COUNT);  //texture::Asteroid12 - Asteroid1 + 1
}


//  update
//----------------------------------------------------------------------------------------------------------------------------------
void Asteroid::update()
{
    float time = timer::frameTime();

    if (visible_)
    {
        physics::collide(this, STATICS | MOBILES);

        if (frozen_ <= 0.f)
        {
            if (sticky_)
                velocity_ = Vector2f();
            else
            {
                Vector2f acceleration; //(physics::attract(this));
                // s = s0 + v0*t + 0.5*a*t*t
                location_ += velocity_*time + acceleration*0.5*time*time;
                // v = v0 + a*t
                velocity_ += acceleration*time + velocity_*(-0.2)*time;
                // spin around
                fmod(rotation_+= rotateSpeed_*time*30, 360);
                rotateSpeed_ -= rotateSpeed_*time*0.2;

                borders();
                if (!settings::bCyclicBorderX)
                {
                    if (location_.x_ < radius_)
                    {   location_.x_ = radius_;
                        velocity_.x_ = -velocity_.x_*0.6;
                    }
                    if (location_.x_ > settings::iMapXsize - radius_)
                    {   location_.x_ = settings::iMapXsize - radius_;
                        velocity_.x_ = -velocity_.x_*0.6;
                    }
                }
                if (!settings::bCyclicBorderY)
                {
                    if (location_.y_ < radius_)
                    {   location_.y_ = radius_;
                        velocity_.y_ = -velocity_.y_*0.6;
                    }
                    if (location_.y_ > settings::iMapYsize - radius_)
                    {   location_.y_ = settings::iMapYsize - radius_;
                        velocity_.y_ = -velocity_.y_*0.6;
                    }
                }
            }

            // heating of Asteroid
            if (heatTimer_ > 0.f)
            {   heatTimer_ -= time;
                if (smokeTimer_ > 0)
                    smokeTimer_ -= time;
                else
                {   smokeTimer_ = 0.3f/(settings::iParticleCount*heatTimer_);
                    for (int i=0; i<5; ++i)
                        particles::spawn(particles::pSmoke, location_+Vector2f::randDirLen()*radius_, velocity_);
                }
            }
        }else
        {
            velocity_ = Vector2f();
            frozen_ -= timer::frameTime()*3.f;

            if (frozen_ <= 0.f)
            {   frozen_ = 0.f;
                // mass_ = 7.f;
                particles::spawnMultiple(2, particles::pCrushedIce, location_);
            }
        }
    }else //if (settings:: ..?
    {
        respawnTimer_ -= time;
        if (respawnTimer_ < 0.2f && (respawnTimer_ + time) >= 0.2f)
            sound::playSound(sound::BallRespawn);
        if (respawnTimer_ <= 0)
            respawn();
    }
}


//  draw
//----------------------------------------------------------------------------------------------------------------------------------
void Asteroid::draw() const
{
    if (visible_)
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0);
        glRotatef(rotation_, 0, 0, 1);

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float r = radius_ * 4.f/2.f;  //par texture
        auto t = (texture::TextureType)(texture::Asteroid1 + type_);

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(t));
        //  pattern
        color_.gl4f();
        glBegin(GL_QUADS);
            glTexCoord2f(0.f, 1.f);  glVertex2f(-r, -r);
            glTexCoord2f(1.f, 1.f);  glVertex2f(-r,  r);
            glTexCoord2f(1.f, 0.f);  glVertex2f( r,  r);
            glTexCoord2f(0.f, 0.f);  glVertex2f( r, -r);
        glEnd();

        /*if (heatTimer_ > 0)
        {   //  hotness
            color_.gl4f(0.05 * heatTimer_);
            glBegin(GL_QUADS);
                glTexCoord2f(0.f,  0.5f);  glVertex2f(-r, -r);
                glTexCoord2f(0.f,  1.f);   glVertex2f(-r,  r);
                glTexCoord2f(0.5f, 1.f);   glVertex2f( r,  r);
                glTexCoord2f(0.5f, 0.5f);  glVertex2f( r, -r);
            glEnd();
        }

        glLoadIdentity();
        glTranslatef(location_.x_, location_.y_, 0);
        //  shading
        color_.gl4f(1.f - 0.05*heatTimer_);
        glBegin(GL_QUADS);
            glTexCoord2f(0.5f, 0.f);   glVertex2f(-r, -r);
            glTexCoord2f(0.5f, 0.5f);  glVertex2f(-r,  r);
            glTexCoord2f(1.f,  0.5f);  glVertex2f( r,  r);
            glTexCoord2f(1.f,  0.f);   glVertex2f( r, -r);
        glEnd();*/

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glPopMatrix();
    }
}


//  collision
//----------------------------------------------------------------------------------------------------------------------------------
void Asteroid::onCollision(SpaceObject* with, Vector2f const& location,
                       Vector2f const& direction, Vector2f const& velocity)
{
    sticky_ = false;
    float strength = velocity.length();

    setDamageSource(with->damageSource());
    // If it is a player that shot or hit the Asteroid
    if (damageSource())
       lastShooter_ = damageSource();

    float unfreeze(0), time = timer::frameTime();
    MobileSpaceObject* mobile = dynamic_cast<MobileSpaceObject*>(with);
    auto vel = mobile ? mobile ->velocity() : Vector2f();
    const float less = 0.2f;

    switch (with->type())
    {
        case spaceObjects::oSun:
            rotateSpeed_ = rotateSpeed_*0.5 + ((velocity_.x_*direction.y_ - direction.x_*velocity_.y_)*0.1)*0.5 * less;
            heatTimer_ = 20;
            // if (strength > 50)
            //     sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            unfreeze = 40.f;
            break;

        case spaceObjects::oShip:
            particles::spawnMultiple(1, particles::pSpark, location, direction, velocity_, Color3f(0.3f, 0.3f, 0.3f));
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            break;

        case spaceObjects::oHome:
        case spaceObjects::oPlanet:
            rotateSpeed_ = rotateSpeed_*0.5 + ((velocity_.x_*direction.y_ - direction.x_*velocity_.y_)*0.1)*0.5 * less;
            if (strength > 50)
                sound::playSound(sound::ShipPlanetCollide, location, (strength-50)/3);
            unfreeze = 10.f;
            break;


        //  Ammo new 2
        case spaceObjects::oAmmoFreezers:  // **
            velocity_ += velocity * 0.6f * time * less;
            break;
        case spaceObjects::oAmmoLightning:  // ~~
            velocity_ += velocity * 0.4f * time * less;
            break;

        case spaceObjects::oAmmoCloud:  // OO
        case spaceObjects::oAmmoPulse:  // ))
            if (heatTimer_ < 20.f)  heatTimer_ += 0.01f;
            velocity_ += velocity * 0.3f * time * less;
            unfreeze = 1.f;
            break;

        //  afk =
        case spaceObjects::oAmmoAFK85:
        case spaceObjects::oAmmoAFK47:
            particles::spawnMultiple(1, particles::pSpark, location,
                vel * 0.3f, velocity_, Color3f(0.3f, 0.3f, 0.3f));
            unfreeze = 1.f;
            break;

        //  rifle  ---
        case spaceObjects::oAmmoGauss:  // --.
            velocity_ += velocity * 0.2f * time * less;
        case spaceObjects::oAmmoLaser:  // ___
            velocity_ += velocity * 0.3f * time * less;
        case spaceObjects::oAmmoRifle2:  // --
            particles::spawnMultiple(10, particles::pSpark, location,
                vel * 0.02f, velocity_, Color3f(0.5f, 0.3f, 0.3f));
            unfreeze = 10.f;
            break;
        case spaceObjects::oAmmoROFLE:
            particles::spawnMultiple(10, particles::pSpark, location,
                vel * 0.5f, velocity_, Color3f(0.3f, 0.3f, 0.3f));
            unfreeze = 10.f;
            break;

        //  guns
        case spaceObjects::oAmmoMinigun:  // ...
        case spaceObjects::oAmmoShotgun2:  // <<
        case spaceObjects::oAmmoShotgun:
            particles::spawnMultiple(1, particles::pSpark, location,
                vel * 0.7f, velocity_, Color3f(0.3f, 0.3f, 0.3f));
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoPlasma:  // o
            velocity_ += velocity * 6.f * time * less;
        case spaceObjects::oAmmoFlubba:
            unfreeze = 10.f;
            break;

        //  flame
        case spaceObjects::oAmmoFlamer2: // ~~
            if (heatTimer_ < 20.f)  heatTimer_ += 0.01f;
            velocity_ += velocity * 0.01f * time * less;
            unfreeze = 1.f;
            break;
        case spaceObjects::oAmmoBurner:
            if (heatTimer_ < 20.f)  heatTimer_ += 0.01f;
            velocity_ += velocity * 0.03f * time * less;
            unfreeze = 1.f;
            break;

        case spaceObjects::oAmmoH2OStorm:
        case spaceObjects::oAmmoH2OMG:
            unfreeze = 1.f;
            break;

        default:;
    }

    if (frozen_ > 0)
    {   frozen_ -= unfreeze;
        if (frozen_ <= 0.f)
        {   frozen_ = 0.f;

            // mass_ = 7.f;
            particles::spawnMultiple(2, particles::pCrushedIce, location_);
        }
    }
}

void Asteroid::onShockWave(Player* source, float intensity)
{
    sticky_ = false;
    if (source)
        setDamageSource(source->ship()->damageSource());
}


void Asteroid::explode()
{
    sound::playSound(sound::PlanetExplode, location_, 40.f);
    physics::causeShockWave(damageSource(), location_, 50.f, 300.f, 3.f);

    particles::spawnMultiple(5 , particles::pFragment, location_, location_, location_, Color3f(0.3f, 0.3f, 0.3f));
    particles::spawnMultiple(70, particles::pDust, location_);
    particles::spawnMultiple(20, particles::pExplode, location_);
    particles::spawnMultiple(8, particles::pBurningFragment, location_);
    particles::spawnMultiple(1, particles::pMiniFlame, location_);
    postFX::   onExplosion();

    location_ = respawnLocation_;
    rotation_ = respawnRotation_;
    velocity_ = Vector2f();
    rotateSpeed_ = 0.f;
    physics::removeMobileObject(this);
    visible_ = false;
    heatTimer_ = 0.f;
    respawnTimer_ = 5.f;
}

void Asteroid::respawn()
{
    physics::addMobileObject(this);
    visible_ = true;
    sticky_  = true;
    sound::playSound(sound::BallRespawn, location_, 100.f);
}
