#pragma once

#include "System/Vector2f.hpp"
#include "Items/PowerUp.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>


class PUReverse : public PowerUp
{
    public:
        PUReverse(Vector2f const& location):
            PowerUp(items::puReverse, location,
                15.f, randomizer::random(8.f, 12.f), 3, 0, Color3f(1.f, 0.2f, 0.8f)){}

        void draw() const override;

    private:
        void refreshLifeTime() override;
};
