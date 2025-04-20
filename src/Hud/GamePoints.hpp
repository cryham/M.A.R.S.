#pragma once

#include "Hud/HudElement.hpp"


class GamePoints: public HudElement
{
    public:
        GamePoints(): timer_(0.f)
        {   }

        void draw() const override;
        void update() override;;

        void display(bool show);

    private:
        float timer_;
};

