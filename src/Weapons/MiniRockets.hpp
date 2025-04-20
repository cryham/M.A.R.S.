#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Mini Rockets.
/// Twin mini rocket launchers, accelerating, blue.

class MiniRockets : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        MiniRockets(Mount* parent):
              Weapon(weapons::wMiniRockets, parent, "MiniRockets")
        {   }

        /// Spawns some particles.
        void fire() const;
        mutable int side_ = 0;

        /// Draws the weapon.
        void draw(float alpha) const;

        /// Returns the maximum distance from which this weapon should be used.
        float maxDistance() const;

        /// Returns the minimum distance from which this weapon should be used.
        float minDistance() const;

        /// Returns the maximum angle from which this weapon should be used.
        float maxAngle()   const;
};
