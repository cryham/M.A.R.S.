#pragma once

#include "DecoObjects/DecoObject.hpp"

#include "Media/texture.hpp"

class Planet;


/// A random sign on a Planet.
/// Very decorative.

class PlanetSign : public DecoObject
{
    public:
        /// Creates a randomly positioned Sign on the target Planet.
        PlanetSign(Planet* planet);

        void draw() const override;

    private:
        texture::TextureType texture_;
        Vector2f location_;
        float rotation_;
        float scale_;
};

