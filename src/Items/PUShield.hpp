#pragma once

#include "System/Vector2f.hpp"
#include "Items/PowerUp.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>


class PUShield: public PowerUp
{
    public:
        PUShield(Vector2f const& location):
            PowerUp(items::puShield, location,
                15.f, randomizer::random(8.f, 12.f), 4, 0, Color3f(0.3f, 0.1f, 1.0f)){}

        void draw() const override;

    private:
        void refreshLifeTime() override;
};
