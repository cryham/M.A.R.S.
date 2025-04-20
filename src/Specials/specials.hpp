#pragma once

class Special;
class Ship;


namespace specials 
{
    enum SpecialType
    {
        sFreeze=0, sHeal, sBlast, sFireWall, sShocker,
        All  // All count  or  no special
    };

    Special* create    (SpecialType type, Ship* parent);
    Special* createNext(SpecialType type, Ship* parent);
    Special* createPrev(SpecialType type, Ship* parent);
}
