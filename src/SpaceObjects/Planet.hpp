#pragma once

#include "SpaceObjects/SpaceObject.hpp"


class Planet: public SpaceObject
{
    public:
        Planet(Vector2f const& location, float radius);

        void update() override
        {   }

        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

    private:
        texture::TextureType texture_;
        Color3f color_;
};

