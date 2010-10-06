/* ammoH2OMGs.hpp

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

# ifndef AMMOH2OMGS_HPP_INCLUDED
# define AMMOH2OMGS_HPP_INCLUDED

# include "Particles/Particle.hpp"

# include <list>

namespace ammoH2OMGs {

    class AmmoH2OMG: public Particle {
        public:
            AmmoH2OMG(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Player* damageSource);

            void update();
            void draw() const;

            void onCollision(SpaceObject* with, Vector2f const& location,
                             Vector2f const& direction, Vector2f const& velocity);

        private:
            Color3f color_;
    };

    void spawn(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity, Player* damageSource);
    void update();
    void draw();
    int  count();
    void clear();
}

# endif // AMMOH2OMGS_HPP_INCLUDED




