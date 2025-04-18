#include "Specials/specials.hpp"

#include "Specials/Blast.hpp"
#include "Specials/Freezer.hpp"
#include "Specials/Heal.hpp"
#include "Specials/FireWall.hpp"
#include "Specials/Shocker.hpp"
#include "Specials/NoSpecial.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"


namespace specials 
{
    SpecialType getNext(SpecialType type, bool add1st = true, int add = 1)
    {
        int next = type, cnt = 0;
        auto check = [&next]()
        {
            if (next >= specials::All)
                next = 0;
            if (next < 0)
                next = specials::All-1;
        };
        if (add1st)
            next += add;
        check();

        while (cnt < specials::All && !settings::bEnabledSpecials[next])
        {
            next += add;
            check();
            ++cnt;
        }
        return (SpecialType)next;
    }

    Special* create(SpecialType type, Ship* parent)
    {
        type = getNext(type, false, 1);  // ensure enabled

        if (parent)
        {
            if  (parent->getOwner()->type() == controllers::cPlayer1 && type != specials::All)
                settings::player1Special = type;
            else if  (parent->getOwner()->type()  == controllers::cPlayer2 && type != specials::All)
                settings::player2Special = type;
        }
        switch (type)
        {
            case sHeal:      return new Heal(parent);
            case sBlast:     return new Blast(parent);
            case sFireWall:  return new FireWall(parent);
            case sFreeze:    return new Freezer(parent);
            case sShocker:   return new Shocker(parent);
            default:         return new NoSpecial(parent);
        }
    }

    Special* createNext(SpecialType type, Ship* parent)
    {
        SpecialType next = getNext(type, 1);
        return create(next, parent);
    }

    Special* createPrev(SpecialType type, Ship* parent)
    {
        SpecialType next = getNext(type, -1);
        return create(next, parent);
    }
}
