/* Mount.cpp

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

#include "Weapons/Mount.hpp"
#include "Players/Player.hpp"


Mount::Mount(float rotation, Player* owner)
    // ,weaponChangeTime_(0.f)
    :owner_(owner)
    // ,radius(1.f)
    ,rotation_(rotation)
    ,rotateSpeed_(1.f)
    // ,left_(0), right_(0)
{
}

Player* Mount::getOwner() const
{
    return owner_;
}

float Mount::rotation() const
{
    return rotation_;
}
