#pragma once

#include "Weapons/Weapon.hpp"
#include "Weapons/weapons.hpp"


/// Weapon: NoWeapon.

class NoWeapon: public Weapon
{
    public:
        /// Ctor which constructs the weapon.
        NoWeapon(Mount* parent):
              Weapon(weapons::All, parent, sf::String("Nothing"))
        {   }

        void fire() const
        {   }

        void draw(float alpha) const
        {   }

        /// Returns the maximum distance from which this weapon should be used.
        float maxDistance() const
        {  return 0.f;  }

        /// Returns the minimum distance from which this weapon should be used.
        float minDistance() const
        {  return 0.f;  }

        /// Returns the maximum angle from which this weapon should be used.
        float maxAngle() const
        {  return 0.f;  }
};
