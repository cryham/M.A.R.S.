#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Burner.
/// A short distance weapon, which burns nearby enemies.

class Burner: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Burner(Mount* parent):
              Weapon(weapons::wBurner, parent, sf::String("WT-FLAMER"))
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
