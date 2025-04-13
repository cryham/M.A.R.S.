/* AmmoInsta.cpp

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

#include "Particles/AmmoInsta.hpp"

#include "System/timer.hpp"
#include "Media/sound.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "TrailEffects/Trail.hpp"
#include "System/Vector2f.hpp"
#include "Teams/Team.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"
#include "defines.hpp"


std::list<AmmoInsta*> AmmoInsta::activeParticles_;


AmmoInsta::AmmoInsta(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
        Color3f const& color, Player* damageSource)
    :Particle<AmmoInsta>(spaceObjects::oAmmoInsta, location, 1.f, 3.0f, 10.0f),
        color_(color)
{
    setDamageSource(damageSource);
    velocity_ = direction.normalize() * 800.f;
    location_ += velocity_ * timer::frameTime()*1.2f;

    trail_ = trailEffects::attach(this, 0.1f, 2.f, 6.f, color_, true);

    color_.v(1.f);
    color_.s(0.3f);
}

AmmoInsta::~AmmoInsta()
{
    trailEffects::detach(this);
}


void AmmoInsta::update()
{
    const int steps(5);
    float time = timer::frameTime()/steps;

    for (int i=0; i < steps; ++i)
    {
        if (!isDead())
        {
            physics::collide(this, STATICS | MOBILES);
            Vector2f acceleration = physics::attract(this) * 60;

            location_ += velocity_*time + acceleration*time*time;
            velocity_ += acceleration*time;
            borders();

            lifeTime_ += time;

            if (i != steps-1)
                trail_->update();
        }else
            break;
    }

    if (location_.x_ < -100 || location_.x_ > settings::iMapXsize + 100 ||
        location_.y_ < -100 || location_.y_ > settings::iMapYsize + 100)
        killMe();
}

void AmmoInsta::draw() const
{
    color_.gl4f();

    Vector2f dir(velocity_ * 0.015f);
    Vector2f side(dir.y_, -1.f*dir.x_);
    side *= 0.13f;

    const Vector2f
        topL(location_ + 2*dir + side),
        topR(location_ + 2*dir - side),
        btmL(location_ - 2*dir + side),
        btmR(location_ - 2*dir - side);

    const int u = 0;
    const float v = 7.f;
    uv8(u, v);         glVertex2f(topL.x_, topL.y_);
    uv8(u, v+0.5f);    glVertex2f(btmL.x_, btmL.y_);
    uv8(u+3, v+0.5f);  glVertex2f(btmR.x_, btmR.y_);
    uv8(u+3, v);       glVertex2f(topR.x_, topR.y_);
}

void AmmoInsta::onCollision(SpaceObject* with, Vector2f const& location,
                        Vector2f const& direction, Vector2f const& velocity)
{
    float strength = (velocity-velocity_).length();

    if (strength > 50.f)
    {
        switch (with->type())
        {
            case spaceObjects::oShip:
                sound::playSound(sound::SniperShipCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oBall:
                sound::playSound(sound::SniperShipCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oPlanet: case spaceObjects::oHome:
                sound::playSound(sound::SniperPlanetCollide, location, (strength-50)/3);
                break;

            case spaceObjects::oSun:
                sound::playSound(sound::SniperPlanetCollide, location, (strength-50)/3);
                break;

            default:;
        }
    }
    killMe();
}


int AmmoInsta::hitsAny(Vector2f const& location, Vector2f const& direction, Team* team)
{
    //glLineWidth(3.f);
    //team->color().gl4f(0.4f);

    float resolution(0.02f + 0.002f * (100 - settings::iBotsDifficulty));

    Vector2f velocity(direction.normalize() * 800.f), from(location);
    from += velocity*timer::frameTime() * 1.2f;

    for (int i=0; i < 10 + settings::iBotsDifficulty * 0.9f; ++i)
    {
        Vector2f acceleration;
        for (const auto& it : physics::getGravitySources())
        {
            float distanceSquared = (from - it->location()).lengthSquare();
            if (distanceSquared > 100.f)
                acceleration += (it->location() - from) * it->mass() / distanceSquared;
        }
        acceleration *= 60.f;
        Vector2f to (from + velocity * resolution + acceleration*resolution*resolution);
        velocity += acceleration*resolution;

       /* glBegin(GL_LINES);
            glVertex2f(from.x_, from.y_);
            glVertex2f(to.x_, to.y_);
        glEnd();*/

        for (const auto& it : ships::getShips())
        {
            if (it->attackable())
            {
                Vector2f shipLocation(it->location() + it->velocity()*resolution*i*0.01f*settings::iBotsDifficulty);
                Vector2f orthoDir(velocity.y_, -velocity.x_);
                orthoDir = orthoDir.normalize()*it->radius();
                Vector2f shipLeft(shipLocation-orthoDir), shipRight(shipLocation+orthoDir);

                if (clockWise(velocity, shipRight-to) && !clockWise(velocity, shipLeft-to) &&
                    clockWise(orthoDir, from-shipRight) && !clockWise(orthoDir, to-shipRight))
                {
                    if (it->getOwner()->team() != team)
                    {
                       /* glPointSize(50.f);
                        glColor3f(0.f, 1.f, 0.f);
                        glBegin(GL_POINTS);
                            glVertex2f(it->location().x_, it->location().y_);
                        glEnd();*/
                        return 100;
                    }else
                    {
                        /*glPointSize(50.f);
                        glColor3f(1.f, 0.f, 0.f);
                        glBegin(GL_POINTS);
                            glVertex2f(it->location().x_, it->location().y_);
                        glEnd();*/
                        return 0;
                    }
                }
            }
        }

        if (to.x_ < -100 || to.x_ > settings::iMapXsize + 100 ||
            to.y_ < -100 || to.y_ > settings::iMapYsize + 100)
            return 0;

        for (const auto& it : physics::getGravitySources())
        {
            if (it->type() != spaceObjects::oBlackHole &&
                (it->location()-to).lengthSquare() < std::pow(it->radius(), 2))
                return 0;
        }
        from = to;
    }
    return 0;
}
