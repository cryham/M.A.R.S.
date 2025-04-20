#pragma once

#include "System/Vector2f.hpp"

#include <list>

class CannonControl;
class PowerUp;


namespace items 
{
    enum PowerUpType
    {
        puShield, puReverse, puSleep, puHealth, puFuel,
        COUNT
    };

    void update();
    void draw();

    void addCannonControl();
    CannonControl* getCannonControl();

    std::list<PowerUp*>const& getPowerUps();

    void clear();
}
