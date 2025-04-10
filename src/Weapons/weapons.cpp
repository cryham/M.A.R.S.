/* weapons.cpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "Weapons/weapons.hpp"

#include "Weapons/AFK47.hpp"
#include "Weapons/Burner.hpp"
#include "Weapons/Fist.hpp"
#include "Weapons/Insta.hpp"
#include "Weapons/Flubba.hpp"
#include "Weapons/H2OMG.hpp"
#include "Weapons/ROFLE.hpp"
#include "Weapons/RocketLauncher.hpp"
#include "Weapons/Shotgun.hpp"
#include "Weapons/NoWeapon.hpp"

#include "Weapons/AFK85.hpp"
#include "Weapons/Flamer2.hpp"
#include "Weapons/Plasma.hpp"
#include "Weapons/H2OStorm.hpp"
#include "Weapons/Rifle2.hpp"
#include "Weapons/MiniRockets.hpp"
#include "Weapons/Shotgun2.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"


namespace weapons 
{
    WeaponType getNext(WeaponType type, bool add1st = true, int add = 1)
    {
        int next = type, cnt = 0;
        auto check = [&next]()
        {
            if (next >= weapons::All)
                next = 0;
            if (next < 0)
                next = weapons::All-1;
        };
        if (add1st)
            next += add;
        check();

        while (cnt < weapons::All && !settings::C_EnabledWeapons[next])
        {
            next += add;
            check();
            ++cnt;
        }
        return (WeaponType)next;
    }

    Weapon* create(WeaponType type, Ship* parent)
    {
        type = getNext(type, false, 1);  // ensure enabled

        if (parent)
        {
            if (parent->getOwner()->type() == controllers::cPlayer1 && type != weapons::All && type != wInsta)
                settings::C_playerIWeapon = type;
            else
            if (parent->getOwner()->type() == controllers::cPlayer2 && type != weapons::All && type != wInsta)
                settings::C_playerIIWeapon = type;
        }
        switch (type)
        {
            case wAFK47:           return new AFK47(parent);
            case wBurner:          return new Burner(parent);
            case wFist:            return new Fist(parent);
            case wFlubba:          return new Flubba(parent);
            case wH2OMG:           return new H2OMG(parent);
            case wROFLE:           return new ROFLE(parent);
            case wRocketLauncher:  return new RocketLauncher(parent);
            case wInsta:           return new Insta(parent);
            case wShotgun:         return new Shotgun(parent);

            // cryham  excessive, modded originals
            case wAFK85:        return new AFK85(parent);
            case wFlamer2:      return new Flamer2(parent);
            case wPlasma:       return new Plasma(parent);
            case wH2OStorm:     return new H2OStorm(parent);
            case wRifle2:       return new Rifle2(parent);
            case wMiniRockets:  return new MiniRockets(parent);
            case wShotgun2:     return new Shotgun2(parent);

            // cryham  new todo..
            // case wMinigun:      return new Minigun(parent);
            // case wGrenades:     return new Grenades(parent);
            // case wLaser:        return new Laser(parent);
            // case wLightning:    return new Lightning(parent);
            default:            return new NoWeapon(parent);
        }
    }

    Weapon* createNext(WeaponType type, Ship* parent)
    {
        WeaponType next = getNext(type, true, 1);
        return create(next, parent);
    }

    Weapon* createPrev(WeaponType type, Ship* parent)
    {
        WeaponType next = getNext(type, true, -1);
        return create(next, parent);
    }
}
