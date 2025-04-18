#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: ROCK'n'LOL.
/// A rocket launcher which aims at nearby enemies.

class Seekers: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        Seekers(Mount* parent):
              Weapon(weapons::wSeekers, parent, "Seekers")
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
