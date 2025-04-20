#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Minigun.
/// A short distance gun, which fires some particles in multiple direction.

class Minigun : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Minigun(Mount* parent):
              Weapon(weapons::wMinigun, parent, sf::String("Minigun"))
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
