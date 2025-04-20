#pragma once

#include "Zones/Zone.hpp"


/// Zone: RasterZone.
/// A square shaped zone.

class RasterZone : public Zone
{
    public:
        /// Ctor, which creates the Zone.
        RasterZone(Vector2f const& btmL, Vector2f const& topR);

        /// Returns true, if the given SpaceObject is inside this Zone.
        bool isInside(SpaceObject const& toBeChecked) const override;

        /// Updates the Zone.
        void update();

        /// Draws the zone.
        /// Only for debugging information.
        void draw() const override;

        /// Returns a random point inside this Zone.
        Vector2f getRandomPoint() const;

        /// Returns true, if this Zone is covered.
        /// A Zone is covered, when the percentage of a teams ships being inside
        /// the Zone is larger than the percentage this zone does to the total
        /// tactical zone area of a team.
        bool covered() const;

    private:
        Vector2f btmL_, topR_;
        bool covered_;
};
