#pragma once

#include "Hud/HudElement.hpp"


class GameStats: public HudElement
{
    public:
        GameStats():
            updateTimer_(0.5f),
            particleCount_(0)
        {   }

        void draw() const override;

    private:
        mutable float updateTimer_;
        mutable int   particleCount_;
};

