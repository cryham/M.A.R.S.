#pragma once

#include "Zones/Zone.hpp"


/// Zone: HomeZone.
/// A large round Zone around the HomePlanet.

class HomeZone : public Zone
{
    public:
        /// Ctor, which creates the Zone.
        HomeZone(Vector2f const& location);

        /// Returns true, if the given SpaceObject is inside this Zone.
        bool isInside(SpaceObject const& toBeChecked) const override;

        /// Draws the zone.
        /// Only for debugging information.
        void draw() const override;

    private:
        float radius_;
        Vector2f location_;
        int homeSide_;
};
