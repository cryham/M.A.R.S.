#pragma once

#include "Hud/HudElement.hpp"


class Logo : public HudElement
{
    public:
        Logo();

        void update() override;
        void draw() const override;

    private:
        float timer_;
        bool  on_;
        int flicCount_;
};


