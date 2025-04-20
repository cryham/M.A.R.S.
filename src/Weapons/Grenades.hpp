#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Grenades.
/// A short distance gun, populates the screen with ugly green bubbles.

class Grenades : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Grenades(Mount* parent):
              Weapon(weapons::wGrenades, parent, sf::String("Grenades"))
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
