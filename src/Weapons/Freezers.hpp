#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Freezers.
/// A short distance gun, populates the screen with ugly green bubbles.

class Freezers : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Freezers(Mount* parent):
              Weapon(weapons::wFreezers, parent, sf::String("Freezers"))
        {   }

        /// Spawns some particles.
        void fire() const;

        /// Draws the weapon.
        void draw(float alpha) const;

        /// Returns the maximum distance from which this weapon should be used.
        float maxDistance() const;

        /// Returns the minimum distance from which this weapon should be used.
        float minDistance() const;

        /// Returns the maximum angle from which this weapon should be used.
        float maxAngle()   const;
};
