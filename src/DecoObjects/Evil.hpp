#pragma once

#include "DecoObjects/DecoObject.hpp"


/// A very evil sign, in Cannon Keep game

class Evil: public DecoObject
{
    public:
        void draw() const override;
};
