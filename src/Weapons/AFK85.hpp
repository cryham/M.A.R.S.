#pragma once

#include "System/Color3f.hpp"
#include "Weapons/Weapon.hpp"


/// Weapon: AFK85.
/// A long distance twin short laser. Double AFK47.

class AFK85 : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        AFK85(Mount* parent);

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

        Color3f color_;
};
