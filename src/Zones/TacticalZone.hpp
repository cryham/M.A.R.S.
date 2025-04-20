#pragma once

#include "Zones/Zone.hpp"


/// Zone: TacticalZone.
/// A round Zone.

class TacticalZone: public Zone
{
    public:
        /// Ctor, which creates the Zone.
        TacticalZone(Vector2f const& location, float radius);

        /// Returns true, if the given SpaceObject is inside this Zone.
        bool isInside(SpaceObject const& toBeChecked) const override;

        /// Updates the Zone.
        void update();

        /// Draws the zone.
        /// Only for debugging information.
        void draw() const override;

        /// Returns a random point inside this Zone.
        Vector2f getRandomPoint() const;

        /// Getter for the loaction.
        Vector2f const& location() const;

        /// Returns true, if this Zone is covered.
        /// A Zone is covered, when the percentage of a teams ships being inside
        /// the Zone is larger than the percentage this zone does to the total
        /// tactical zone area of a team.
        bool covered() const;

        friend class BotController;

    private:
        float radius_;
        Vector2f location_;
        short homeSide_;
        bool covered_;
        float  shipCount_;
};
