#pragma once

#include "System/timer.hpp"
#include "Weapons/weapons.hpp"
#include "Weapons/Mount.hpp"

class Mount;  // Ship or Turret


/// A virtual base class for all weapons.
/// Provides a basic interface for all weapons, some base members and methodes.

class Weapon
{
    public:
        /// Ctor which constructs the base Weapon.
        Weapon(weapons::WeaponType type, Mount* parent, sf::String name);
        virtual ~Weapon()
        {   }

        /// This function is called whenever the weapon is fired.
        virtual void fire() const = 0;

        /// Draws the weapon.
        virtual void draw(float alpha) const = 0;


        /// Returns the name of the Weapon.
        sf::String const& getName() const
        {   return name_;  }

        /// Returns the type of the Weapon.
        weapons::WeaponType getType() const
        {   return type_;  }


        /// Returns the maximum distance from which this weapon should be used.
        virtual float maxDistance() const = 0;

        /// Returns the minimum distance from which this weapon should be used.
        virtual float minDistance() const = 0;

        /// Returns the maximum angle from which this weapon should be used.
        virtual float maxAngle()   const = 0;

    protected:
        Mount* parent_;
        mutable float timer_;

    private:
        sf::String name_;
        weapons::WeaponType type_;
};
