/* Shotgun.hpp

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

# ifndef SHOTGUN_HPP_INCLUDED
# define SHOTGUN_HPP_INCLUDED

# include "Weapons/Weapon.hpp"

class Shotgun: public Weapon {
    public:
        Shotgun(Ship* parent):
              Weapon(parent, "SHOTGUN") {};

        void fire() const;
        void draw() const;

        void next();
        void previous();
};

# endif // SHOTGUN_HPP_INCLUDED


