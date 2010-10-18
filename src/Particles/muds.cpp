/* muds.cpp

Copyright (c) 2010 by Felix Lauer and Simon Schneegans

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

# include "Particles/muds.hpp"

# include "System/timer.hpp"

namespace muds {

    namespace {
        std::list<Mud*> activeParticles_;
    }

    Mud::Mud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Color3f const& color):
             Particle(spaceObjects::oMud, location, 1, 0, sf::Randomizer::Random(0.6f, 0.8f)),
             color_(color) {

        Vector2f distortion(Vector2f::randDirLen());
        velocity_ = direction + distortion*150;
    }

    void Mud::update() {
        // update Color
        color_.v(-1.0/totalLifeTime_*lifeTime_+1);

        float time = timer::frameTime();
        Vector2f acceleration = physics::attract(this);

        location_ += velocity_*time + acceleration*time*time*5;
        velocity_ += acceleration*time*5 + velocity_*-2*time;

        lifeTime_ += time;
    }

    void Mud::draw() const {
        color_.gl3f();
        glVertex2f(location_.x_, location_.y_);
    }


    void spawn(Vector2f const& location, Vector2f const& direction, Vector2f const& sourceVelocity, Color3f const& color) {
        activeParticles_.push_back(new Mud(location, direction, sourceVelocity, color));
    }

    void draw() {

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glPointSize(1);
        glBegin(GL_POINTS);

        for (std::list<Mud*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            (*it)->draw();

        glEnd();
    }

    void update() {
        std::list<Mud*>::iterator it = activeParticles_.begin();
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
        for (std::list<Mud*>::iterator it = activeParticles_.begin(); it != activeParticles_.end(); ++it)
            delete *it;
        activeParticles_.clear();
    }
}
