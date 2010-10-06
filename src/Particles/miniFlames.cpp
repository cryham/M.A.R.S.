/* miniFlames.cpp

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

# include "Particles/miniFlames.hpp"

# include "System/timer.hpp"
# include "System/settings.hpp"
# include "Particles/particles.hpp"

namespace miniFlames {

    namespace {
        std::list<MiniFlame*> activeParticles_;
    }

    MiniFlame::MiniFlame(Vector2f const& location):
               Particle(spaceObjects::oMiniFlame, location+Vector2f::randDir(), 1.f, 0.f, sf::Randomizer::Random(1.5f, 2.5f)*settings::C_globalParticleLifeTime/100.f) {

        flickerSpeed_ = sf::Randomizer::Random(0.01f, 1.f);
        timer_        = sf::Randomizer::Random(0.f, 0.5f);
        radius_       = sf::Randomizer::Random(2.0f, 5.0f);

        color_.h(60+350);
        color_.v(0.2);
        color_.s(1);
    }

    void MiniFlame::update() {
        float time = timer::frameTime();
        // update Color
        color_.h((-1.0/totalLifeTime_*lifeTime_+1)*60+0);

        if (std::fmod(lifeTime_, flickerSpeed_) < 0.01f)
            color_ = Color3f(1.f, 0.8f, 0.3f);
        else {
            color_.s(1.f);
            color_.v(-0.2f/totalLifeTime_*lifeTime_+0.2f);
        }

        location_ += Vector2f::randDirLen()*0.3f;

        if (timer_ > 0.f)
            timer_ -= time;
        else {
            timer_ = 0.5f;
             particles::spawn(particles::pSmoke, location_, velocity_);
        }

        lifeTime_ += time;
    }

    void MiniFlame::draw() const {
        color_.gl3f();
        const int posX = 5;
        const int posY = 0;
        glTexCoord2f(posX*0.125f,     posY*0.125f);     glVertex2f(location_.x_-radius_, location_.y_-radius_);
        glTexCoord2f(posX*0.125f,     (posY+1)*0.125f); glVertex2f(location_.x_-radius_, location_.y_+radius_);
        glTexCoord2f((posX+1)*0.125f, (posY+1)*0.125f); glVertex2f(location_.x_+radius_, location_.y_+radius_);
        glTexCoord2f((posX+1)*0.125f, posY*0.125f);     glVertex2f(location_.x_+radius_, location_.y_-radius_);
    }


    void spawn(Vector2f const& location) {
        activeParticles_.push_back(new MiniFlame(location));
    }

    void draw() {
        for (std::list<MiniFlame*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            (*it)->draw();
    }

    void update() {
        std::list<MiniFlame*>::iterator it = activeParticles_.begin();
        while (it != activeParticles_.end()) {
            (*it)->update();
            if ((*it)->isDead()) {
                delete *it;
                it = activeParticles_.erase(it);
            }
            else ++it;
        }
    }

    int count() {
        return activeParticles_.size();
    }

    void clear() {
        for (std::list<MiniFlame*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            delete *it;
        activeParticles_.clear();
    }
}


