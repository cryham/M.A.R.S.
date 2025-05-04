#include "Weapons/Weapon.hpp"


Weapon::Weapon(weapons::WeaponType type, Mount* parent, sf::String name):
    parent_(parent),
    timer_(0),
    type_(type),
    name_(name)
{   }
