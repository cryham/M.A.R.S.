#pragma once

#include "DecoObjects/DecoObject.hpp"
// #include "Media/texture.hpp"

class Sun;


/// A heat texture on a Sun.
/// Very decorative.

class SunHeat: public DecoObject
{
    public:
        /// Creates a heat texture on the target Sun.
        SunHeat(Sun* sun);

        /// Draws the texture.
        void draw() const override;

    private:
        Vector2f location_;
        float radius_;
};
