#pragma once

#include "Weapons/Weapon.hpp"


/// Weapon: H2OMG.
/// A long distance gun, which fires some icy cubes.

class H2OMG : public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        H2OMG(Mount* parent):
              Weapon(weapons::wH2OMG, parent, sf::String("H2O-MG"))
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
