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
        wInsta = 0,
        wAFK47, wBurner, wFist, wFlubba,  // original
        wShotgun, wRocketLauncher, wROFLE, wH2OMG,
                     
        wShotgun2, wPlasma, wMiniRockets, wFlamer2,  // cryham excessive, modded originals
        wAFK85, wRifle2, wH2OStorm,
        // wCloud, wFreezers, wGauss,  // cryham new todo
        // wGrenades, wLaser, wLightning, wMinigun, wPulse, wSeekers,
        All  // All count  or  no weapon
    };

    Weapon* create    (WeaponType type, Ship* parent);
    Weapon* createNext(WeaponType type, Ship* parent);
    Weapon* createPrev(WeaponType type, Ship* parent);
}
