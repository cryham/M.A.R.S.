/* CannonControl.hpp

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

# ifndef CANNONCONTROL_HPP_INCLUDED
# define CANNONCONTROL_HPP_INCLUDED

# include "Items/Item.hpp"

class Player;

class CannonControl: public Item {
    public:
        CannonControl(Vector2f const& location);

        Ship* update();
        void draw() const;

        Player* getCarrier() const;

    private:
        Ship* ship_;
        Vector2f respawnLocation_;
};

# endif // CANNONCONTROL_HPP_INCLUDED






