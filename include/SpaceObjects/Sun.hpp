#pragma once

#include "SpaceObjects/SpaceObject.hpp"
#include "System/Color3f.hpp"


class Sun: public SpaceObject
{
    public:
        Sun(Vector2f const& location, float radius, int type);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

    private:
        float eruptionTimer_;

        int type_;  // 0 yellow-orange, 1 white-blue, 2 red-brown
        Color3f color_;
};
