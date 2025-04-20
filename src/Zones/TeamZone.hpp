#pragma once

#include "Zone.hpp"


/// Zone: TutorialZone.
/// A very large Zone, covering half the screen.

class TeamZone : public Zone
{
    public:
        /// Ctor, which creates the Zone.
        TeamZone(int homeSide) :
            Zone(),
            homeSide_(homeSide)
        {   }

        /// Returns true, if the given SpaceObject is inside this Zone.
        bool isInside(SpaceObject const& toBeChecked) const override;

        /// Draws the zone.
        /// Only for debugging information.
        void draw() const override;

    private:
        int homeSide_;
};
