#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: ROCK'n'LOL.
/// A launcher of big, old, slow rocket, which aims at nearby enemies.

class OldRocket: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        OldRocket(Mount* parent):
              Weapon(weapons::wOldRocket, parent, "ROCK'n'LOL")
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
