/* explodes.cpp

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

# include "Particles/explodes.hpp"

# include "System/timer.hpp"
# include "System/settings.hpp"

namespace explodes {

    namespace {
        std::list<Explode*> activeParticles_;
    }

    Explode::Explode(Vector2f const& location):
               Particle(spaceObjects::oExplode, location, 4, 0, sf::Randomizer::Random(0.2f, 0.4f)) {

        velocity_ = Vector2f::randDir()*150*sf::Randomizer::Random(0.2f, 2.f);

        color_ = Color3f(1.0f, 0.5f, 0.2f);
    }

    void Explode::update() {
        float time = timer::frameTime();

        color_.v(-1.0/totalLifeTime_*lifeTime_+1);
        // update Size
        radius_ = lifeTime_*100+5;

        location_ = location_ + velocity_*time;
        velocity_ = velocity_ + velocity_*(-2)*time;

        lifeTime_ += time;
    }

    void Explode::draw() const {
        color_.gl4f(0.2);
        glTexCoord2i(0, 0); glVertex2f(location_.x_-radius_, location_.y_-radius_);
        glTexCoord2i(0, 1); glVertex2f(location_.x_-radius_, location_.y_+radius_);
        glTexCoord2i(1, 1); glVertex2f(location_.x_+radius_, location_.y_+radius_);
        glTexCoord2i(1, 0); glVertex2f(location_.x_+radius_, location_.y_-radius_);
    }

    void spawn(Vector2f const& location) {
        activeParticles_.push_back(new Explode(location));
    }

    void draw() {
        glEnable(GL_TEXTURE_2D);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Explode));
        glBegin(GL_QUADS);

        for (std::list<Explode*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            (*it)->draw();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void update() {
        std::list<Explode*>::iterator it = activeParticles_.begin();
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
        for (std::list<Explode*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            delete *it;
        activeParticles_.clear();
    }
}


