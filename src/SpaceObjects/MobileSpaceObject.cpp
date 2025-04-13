/* MobileSpaceObject.hpp

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

#include "SpaceObjects/MobileSpaceObject.hpp"
#include "System/settings.hpp"


//  cyclic borders
void MobileSpaceObject::borders()
{
    if (settings::C_CyclicBorderX)
    {
        if (location_.x_ < 0.f)
            location_.x_ += settings::C_MapXsize;
        
        if (location_.x_ > settings::C_MapXsize)
            location_.x_ -= settings::C_MapXsize;
    }
    if (settings::C_CyclicBorderY)
    {
        if (location_.y_ < 0.f)
            location_.y_ += settings::C_MapYsize;
        
        if (location_.y_ > settings::C_MapYsize)
            location_.y_ -= settings::C_MapYsize;
    }
/*
    if (settings::C_cyclicBorderX)
    {
        if (location_.x_ < radius_)
            location_.x_ = settings::C_MapXsize - radius_;
        
        if (location_.x_ > settings::C_MapXsize - radius_)
            location_.x_ = radius_;
    }
    if (settings::C_cyclicBorderY)
    {
        if (location_.y_ < radius_)
            location_.y_ = settings::C_MapYsize - radius_;
        
        if (location_.y_ > settings::C_MapYsize - radius_)
            location_.y_ = radius_;
    }
*/
}
