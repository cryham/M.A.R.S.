#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: ROFLE.
/// A long distance gun, a sniper.

class ROFLE: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        ROFLE(Mount* parent):
              Weapon(weapons::wROFLE, parent, sf::String("ROFLE"))
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
