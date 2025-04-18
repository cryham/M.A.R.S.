/* MobileSpaceObject.hpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

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

#include "SpaceObjects/SpaceObject.hpp"


class MobileSpaceObject: public SpaceObject
{
    public:
        MobileSpaceObject(spaceObjects::ObjectType type, Vector2f location, float radius, float mass)
            :SpaceObject(type, location, radius, mass)
        {   }

        Vector2f& velocity()
        {  return velocity_;  }

        //  cyclic borders
        void borders();

        bool cloud_ = false;  // no collision, can overlap,  cloud, plasma etc
        float chill_ = 0.f;

    protected:
        Vector2f velocity_;
        float acceleration_ = 0.f;
};
