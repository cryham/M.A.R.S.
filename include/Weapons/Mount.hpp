/* Mount.hpp

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

#include "System/Vector2f.hpp"

class Player;


//  rotating mount for weapon, base for Ship and Turret

class Mount
{
    public:
        Mount(float rotation = 0.f, Player* owner = NULL);

        Player* getOwner() const;

        float   rotation() const;
        virtual float    getRadius() = 0;

        virtual Vector2f getLocation() = 0;
        virtual Vector2f& getVelocity() = 0;

    protected:

        Player* owner_;

        // float radius_;

        float rotation_;
        float rotateSpeed_;
        // int left_, right_;  // inputs
};
