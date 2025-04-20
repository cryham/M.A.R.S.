#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Lightning.
/// A short distance gun, populates the screen with ugly green bubbles.

class Lightning : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Lightning(Mount* parent):
              Weapon(weapons::wLightning, parent, sf::String("Lightning"))
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
