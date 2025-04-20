#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: Fist.
/// A short distance gun, which pwnes nearby enemies

class Fist: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Fist(Mount* parent);

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

    private:
        mutable float position_;
        Color3f color_;
};
