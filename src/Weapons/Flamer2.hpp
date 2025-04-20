#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Flamer2.
/// A short distance weapon, which burns nearby enemies.

class Flamer2: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Flamer2(Mount* parent):
              Weapon(weapons::wFlamer2, parent, sf::String("Flamer2"))
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
