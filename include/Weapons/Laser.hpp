#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Rifle2.
/// A long distance gun, a sniper.

class Laser: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Laser(Mount* parent):
              Weapon(weapons::wLaser, parent, sf::String("Laser"))
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
