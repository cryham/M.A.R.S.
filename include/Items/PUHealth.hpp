#pragma once

#include "System/Vector2f.hpp"
#include "Items/PowerUp.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>


class PUHealth: public PowerUp
{
    public:
        PUHealth(Vector2f const& location):
            PowerUp(items::puHealth, location,
                15.f, randomizer::random(8.f, 12.f), 0, 1, Color3f(1.f, 0.6f, 0.8f)){}

        void draw() const override;

    private:
        void refreshLifeTime() override;
};
