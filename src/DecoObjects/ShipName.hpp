#pragma once

#include "DecoObjects/DecoObject.hpp"

class Ship;


/// An object displaying the players name at his Ship.

class ShipName: public DecoObject
{
    public:
        ShipName(Ship* ship, bool bar)
            :ship_(ship), bar_(bar)
        {   }

        void draw() const override;

    private:
        Ship* ship_;
        bool bar_;  // only bar, no text
};
