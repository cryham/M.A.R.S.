/* AmmoSeekers.hpp

Copyright (c) 2025 Crystal Hammer

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

#pragma once

#include "Particles/Particle.hpp"

#include "System/Color3f.hpp"

class Ship;
class Ball;


class AmmoSeekers: public Particle<AmmoSeekers>
{
    public:
        AmmoSeekers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoSeekers();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoSeekers>;
        template <typename Object> friend class Ice;
        friend class Freezer;

    private:
        Color3f color_;
        float timer_;

        Ship* shipTarget_;
        Ball* ballTarget_;
        Player* parent_;

        float rotation_;
        float life_;

        float frozen_;
        bool visible_;

        static std::list<AmmoSeekers*> activeParticles_;
};
