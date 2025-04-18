#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Pulse.
/// A short distance gun, populates the screen with ugly green bubbles.

class Pulse: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Pulse(Mount* parent):
              Weapon(weapons::wPulse, parent, sf::String("Pulse"))
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
