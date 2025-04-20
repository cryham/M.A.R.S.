#pragma once

#include "DecoObjects/DecoObject.hpp"


/// The cannon, displayed at the top of the screen when playing CannonKeep.

class Cannon: public DecoObject
{
    public:
        Cannon();

        void update();
        void draw() const override;

    private:
        float timer_;
        float rotation_;
};
