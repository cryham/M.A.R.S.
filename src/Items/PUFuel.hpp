#pragma once

#include "System/Vector2f.hpp"
#include "Items/PowerUp.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>


class PUFuel : public PowerUp
{
    public:
        PUFuel(Vector2f const& location):
            PowerUp(items::puFuel, location,
                15.f, randomizer::random(8.f, 12.f), 3, 1, Color3f(1.f, 1.f, 0.2f)){}

        void draw() const override;

    private:
        void refreshLifeTime() override;
};
