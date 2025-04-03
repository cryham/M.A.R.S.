/* weapons.hpp

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

#pragma once

class Weapon;
class Ship;

namespace weapons 
{
    enum WeaponType
	{
        wInsta = 1<<0,
        wAFK47 = 1<<1, wBurner = 1<<2, wFist = 1<<3, wFlubba = 1<<4,  // original
        wShotgun = 1<<5, wRocketLauncher = 1<<6, wROFLE = 1<<7, wH2OMG = 1<<8,
                     
        wShotgun2 = 1<<9, wPlasma = 1<<10, wMiniRockets = 1<<11, wFlamer2 = 1<<12,  // cryham excessive, modded originals
        wAFK85 = 1<<13, wRifle2 = 1<<14, wH2OStorm = 1<<15,
        // wMinigun = 1<<16, wGrenades = 1<<17, wLaser = 1<<18, wLightning = 1<<19,  // cryham new todo
        wNoWeapon = 1<<20
    };

    Weapon* create    (WeaponType type, Ship* parent);
    Weapon* createNext(WeaponType type, Ship* parent);
    Weapon* createPrev(WeaponType type, Ship* parent);
}
