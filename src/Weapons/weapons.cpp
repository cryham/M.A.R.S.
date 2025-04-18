#include "Weapons/weapons.hpp"

#include "System/Color3f.hpp"
#include "Weapons/AFK47.hpp"
#include "Weapons/Burner.hpp"
#include "Weapons/Fist.hpp"
#include "Weapons/Insta.hpp"
#include "Weapons/Flubba.hpp"
#include "Weapons/H2OMG.hpp"
#include "Weapons/ROFLE.hpp"
#include "Weapons/OldRocket.hpp"
#include "Weapons/Shotgun.hpp"
#include "Weapons/NoWeapon.hpp"

#include "Weapons/AFK85.hpp"
#include "Weapons/Flamer2.hpp"
#include "Weapons/Plasma.hpp"
#include "Weapons/H2OStorm.hpp"
#include "Weapons/Rifle2.hpp"
#include "Weapons/MiniRockets.hpp"
#include "Weapons/Shotgun2.hpp"

#include "Weapons/Pulse.hpp"
#include "Weapons/Cloud.hpp"
#include "Weapons/Freezers.hpp"
#include "Weapons/Laser.hpp"
#include "Weapons/Lightning.hpp"

#include "Weapons/Minigun.hpp"
#include "Weapons/Gauss.hpp"
#include "Weapons/Grenades.hpp"
#include "Weapons/Seekers.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"
#include <cstdlib>


namespace weapons 
{
    WeaponType random()
    {
        int next = 0, cnt = 0;
        do
        {   next = rand() % weapons::All;
            ++cnt;
        }
        while (cnt < weapons::All && !settings::bEnabledWeapons[next]);
        return (WeaponType)next;
    }

    WeaponType getNext(WeaponType type, bool add1st, int add)
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

        while (cnt < weapons::All && !settings::bEnabledWeapons[next])
        {
            next += add;
            check();
            ++cnt;
        }
        return (WeaponType)next;
    }

    //  create
    //----------------------------------------------------------------
    Weapon* create(WeaponType type, Mount* parent)
    {
        type = getNext(type, false, 1);  // ensure enabled

        if (parent && parent->getOwner())
        {
            if (parent->getOwner()->type() == controllers::cPlayer1 && type != weapons::All && type != wInsta)
                settings::player1Weapon = type;
            else
            if (parent->getOwner()->type() == controllers::cPlayer2 && type != weapons::All && type != wInsta)
                settings::player2Weapon = type;
        }
        switch (type)
        {
            case wAFK47:        return new AFK47(parent);
            case wBurner:       return new Burner(parent);
            case wFist:         return new Fist(parent);
            case wFlubba:       return new Flubba(parent);
            case wH2OMG:        return new H2OMG(parent);
            case wROFLE:        return new ROFLE(parent);
            case wOldRocket:    return new OldRocket(parent);
            case wInsta:        return new Insta(parent);
            case wShotgun:      return new Shotgun(parent);

            // cryham  7 excessive,  modded originals
            case wAFK85:        return new AFK85(parent);
            case wFlamer2:      return new Flamer2(parent);
            case wPlasma:       return new Plasma(parent);
            case wH2OStorm:     return new H2OStorm(parent);
            case wRifle2:       return new Rifle2(parent);
            case wMiniRockets:  return new MiniRockets(parent);
            case wShotgun2:     return new Shotgun2(parent);

            // cryham  9 new
            case wPulse:        return new Pulse(parent);
            case wCloud:        return new Cloud(parent);
            case wFreezers:     return new Freezers(parent);
            case wLaser:        return new Laser(parent);
            case wLightning:    return new Lightning(parent);

            case wMinigun:      return new Minigun(parent);
            case wGauss:        return new Gauss(parent);
            case wGrenades:     return new Grenades(parent);
            case wSeekers:      return new Seekers(parent);

            default:            return new NoWeapon(parent);
        }
    }

    //  Weapon name colors for Gui, Hud text after change
    //----------------------------------------------------------------
    Color3f colors[WeaponType::All] =
    {
        //  original  8x
        Color3f(1.0, 0.8, 0.8),  //  Insta-  not on Gui
        Color3f(0.4, 0.5, 0.9),  //  AFK47
        Color3f(0.8, 0.4, 0.1),  //  Flamer/Burner

        Color3f(0.4, 0.9, 0.6),  //  Fist
        Color3f(0.2, 0.8, 0.1),  //  Flubba

        Color3f(0.8, 0.8, 0.3),  //  Shotgun
        Color3f(0.8, 0.4, 0.2),  //  OldRocket ROCK'n'LOL
        Color3f(0.8, 0.2, 0.2),  //  ROFLE

        Color3f(0.4, 0.5, 0.9),  //  H2OMG
        //  new 2  7x excessive mod
        Color3f(0.8, 0.5, 1.0),  //  Shotgun2
        Color3f(0.5, 0.9, 0.9),  //  Plasma
        Color3f(0.2, 0.5, 1.0),  //  MiniRockets

        Color3f(1.0, 0.7, 0.2),  //  Flamer2
        Color3f(0.6, 0.6, 1.0),  //  AFK85

        Color3f(0.9, 0.2, 0.3),  //  Rifle2
        Color3f(0.4, 0.65,1.0),  //  H2OStorm  oo
        //  new 3  9x new
        Color3f(1.0, 0.5, 0.8),  //  Pulse  ))
        Color3f(0.6, 0.6, 1.0),  //  Cloud  OO
        Color3f(0.2, 0.7, 0.9),  //  Freezers  **

        Color3f(1.0, 0.5, 0.0),  //  Laser  ___
        Color3f(0.6, 0.8, 1.0),  //  Lightning  -x
        Color3f(1.0, 1.0, 0.3),  //  Minigun  ...
        Color3f(0.8, 0.2, 0.2),  //  Gauss  --.
        
        Color3f(0.4, 0.5, 0.6),  //  Grenades  o*
        Color3f(0.7, 0.8, 0.6),  //  Seekers  ~
    };

}
