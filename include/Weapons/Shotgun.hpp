#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Shotgun.
/// A short distance gun, which fires some particles in multiple direction.

class Shotgun: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Shotgun(Mount* parent):
              Weapon(weapons::wShotgun, parent, sf::String("SHOTGUN"))
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
