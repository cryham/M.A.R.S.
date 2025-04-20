#pragma once

#include "Zones/Zone.hpp"


/// Zone: TutorialZone.
/// A beautiful pinkish Zone, employed in the Tutorial.

class TutorialZone: public Zone
{
    public:
        /// Ctor, which creates the Zone.
        TutorialZone(Vector2f const& location, float radius);

        /// Returns true, if the given SpaceObject is inside this Zone.
        bool isInside(SpaceObject const& toBeChecked) const override;

        /// Draws the zone.
        void draw() const override;

    private:
        const float radius_;
        Vector2f location_;
};
