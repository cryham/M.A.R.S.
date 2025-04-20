#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Plasma.
/// A short distance gun, populates the screen with ugly green bubbles.

class Plasma : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Plasma(Mount* parent):
              Weapon(weapons::wPlasma, parent, sf::String("Plasma"))
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
