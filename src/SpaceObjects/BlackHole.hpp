#pragma once

#include "SpaceObjects/SpaceObject.hpp"
#include "System/Color3f.hpp"


class BlackHole: public SpaceObject
{
    public:
        BlackHole(Vector2f const& location, float radius);

        void update() override;;
        void draw() const override;

    private:
        float rotation_;
        Color3f color_;
};
