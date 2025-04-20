#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: H2O-Storm.
/// A long distance heavy wind storm.

class H2OStorm: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        H2OStorm(Mount* parent):
              Weapon(weapons::wH2OStorm, parent, sf::String("H2o-Storm"))
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
