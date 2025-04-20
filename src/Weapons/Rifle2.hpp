#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Rifle2.
/// A long distance gun, a sniper.

class Rifle2 : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Rifle2(Mount* parent):
              Weapon(weapons::wRifle2, parent, sf::String("Rifle2"))
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
