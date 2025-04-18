#pragma once

#include "System/Vector2f.hpp"
#include "Items/PowerUp.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>


class PUSleep: public PowerUp
{
    public:
        PUSleep(Vector2f const& location):
            PowerUp(items::puSleep, location,
                15.f, randomizer::random(8.f, 12.f), 2, 0, Color3f(0.6f, 1.f, 0.4f)){}

        void draw() const override;

    private:
        void refreshLifeTime() override;
};
