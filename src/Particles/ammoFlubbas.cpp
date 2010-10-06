/* ammoFlubbas.cpp

Copyright (c) 2010 by Felix Lauer und Simon Schneegans

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

# include "Particles/ammoFlubbas.hpp"

# include "System/timer.hpp"
# include "System/settings.hpp"
# include "Particles/particles.hpp"
# include "Media/sound.hpp"

namespace ammoFlubbas {

    namespace {
        std::list<AmmoFlubba*> activeParticles_;
    }

    AmmoFlubba::AmmoFlubba(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Player* damageSource):
               Particle(spaceObjects::oAmmoFlubba, location, 8.f, 0.4f, sf::Randomizer::Random(9.f, 11.f)) {

        setDamageSource(damageSource);
        velocity_ = velocity + direction*400;
        location_ += velocity_*timer::frameTime()*1.2f;

        radius_ = sf::Randomizer::Random(6.f, 8.f);

        color_ = Color3f(sf::Randomizer::Random(0.0f, 0.4f), sf::Randomizer::Random(0.8f, 1.f), sf::Randomizer::Random(0.0f, 0.4f));
    }

    void AmmoFlubba::update() {
        float time = timer::frameTime();

        physics::collide(this, STATICS | MOBILES);

        // update Size
        if (lifeTime_ > totalLifeTime_-0.3f)
            radius_ = -400.0*pow(lifeTime_+0.2-totalLifeTime_, 2)+12;

        location_ = location_ + velocity_*time;
        velocity_ = velocity_ + velocity_*(-8.f)*time;

        lifeTime_ += time;

        if (lifeTime_ > totalLifeTime_) {
            particles::spawnMultiple(2, particles::pMud, location_, Vector2f(), Vector2f(), color_);
            int rand = sf::Randomizer::Random(5, 10);
            sound::playSound(sound::BlubCollide, location_);
            for (int i=0; i<rand; ++i)
                particles::spawn(particles::pMiniAmmoFlubba, location_);
        }
    }

    void AmmoFlubba::draw() const {
        color_.gl4f(0.8f);
        const int posX = 4;
        const int posY = 0;
        glTexCoord2f(posX*0.125f,     posY*0.125f);     glVertex2f(location_.x_-radius_, location_.y_-radius_);
        glTexCoord2f(posX*0.125f,     (posY+1)*0.125f); glVertex2f(location_.x_-radius_, location_.y_+radius_);
        glTexCoord2f((posX+1)*0.125f, (posY+1)*0.125f); glVertex2f(location_.x_+radius_, location_.y_+radius_);
        glTexCoord2f((posX+1)*0.125f, posY*0.125f);     glVertex2f(location_.x_+radius_, location_.y_-radius_);
    }

    void AmmoFlubba::onCollision(SpaceObject* with, Vector2f const& location,
                             Vector2f const& direction, Vector2f const& velocity) {

        physics::causeShockWave(this, 150.f, 200.f);
        sound::playSound(sound::BlubCollide, location_);
        killMe();
    }

    void spawn(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Player* damageSource) {
        activeParticles_.push_back(new AmmoFlubba(location, direction, velocity, damageSource));
    }

    void draw() {
        for (std::list<AmmoFlubba*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            (*it)->draw();
    }

    void update() {
        std::list<AmmoFlubba*>::iterator it = activeParticles_.begin();
        while (it != activeParticles_.end()) {
            (*it)->update();
            if ((*it)->isDead()) {
                delete *it;
                it = activeParticles_.erase(it);
            }
            else ++it;
        }
    }

    void shockWave(SpaceObject* source, float strength, float radius) {
        for (std::list<AmmoFlubba*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it) {
            Vector2f direction((*it)->location_ - source->location());
            float distance = direction.length();
            if (distance < radius && direction != Vector2f()) {
                float intensity = radius-distance;
                direction = direction.normalize();
                direction *= intensity;
                (*it)->velocity_ += direction;
            }
        }
    }

    int count() {
        return activeParticles_.size();
    }

    void clear() {
        for (std::list<AmmoFlubba*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            delete *it;
        activeParticles_.clear();
    }
}


