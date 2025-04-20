#pragma once

#include "System/Color3f.hpp"

class Weapon;
class Mount;


namespace weapons
{
    enum WeaponType
	{
        wInsta = 0,  // original 8+1
        wAFK47, wBurner, wFist, wFlubba,
        wShotgun, wOldRocket, wROFLE, wH2OMG,
        //  cryham 7 excessive
        wShotgun2, wPlasma, wMiniRockets, wFlamer2,
        wAFK85, wRifle2, wH2OStorm,
        //  cryham 9 new todo
        wPulse, wCloud, wFreezers, wLaser, wLightning,
        wMinigun, wGauss, wGrenades, wSeekers,
        All  // All count  or  no weapon  25
    };

    extern Color3f colors[WeaponType::All];

    Weapon* create    (WeaponType type, Mount* parent);
    WeaponType random();
    WeaponType getNext(WeaponType type, bool add1st = true, int add = 1);
}
