/* specials.cpp

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

        while (cnt < specials::All && !settings::C_EnabledSpecials[next])
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

        if  (parent->getOwner()->type() == controllers::cPlayer1 && type != specials::All)
            settings::C_playerISpecial = type;
        else if  (parent->getOwner()->type()  == controllers::cPlayer2 && type != specials::All)
            settings::C_playerIISpecial = type;

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
