#pragma once

#include "SpaceObjects/SpaceObject.hpp"
#include "Players/Player.hpp"

#include <float.h>


class Home : public SpaceObject
{
    public:
        Home(Vector2f const& location, int life, float radius, float mass,
            Color3f const& color);

        void update() override;;
        void draw() const override;
        void drawLife() const;

        int getLife() const;

        void createShips(std::vector<Player*>& inhabitants) const;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

    private:
        void explode();

        Color3f color_;
        int life_;
        bool visible_;
};
