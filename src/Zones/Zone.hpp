#pragma once

#include "System/Vector2f.hpp"

class SpaceObject;


/// Basic interface for all Zones.

class Zone
{
    public:
        virtual ~Zone()
        {   }

        /// Returns true, if the given SpaceObject is inside this Zone.
        virtual bool isInside(SpaceObject const& toBeChecked) const = 0;

        /// Draws the zone.
        /// Only for debugging information.
        virtual void draw() const = 0;
};
