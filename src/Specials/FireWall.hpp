#pragma once

#include "Specials/Special.hpp"


/// Special: FireWall.
/// A fire wave.

class FireWall : public Special
{
    public:
        /// Ctor which constructs the special.
        FireWall(Ship* parent):
              Special(specials::sFireWall, parent, sf::String("FIRE WALL")),
              burnTimer_(0.f)
        {   }

        /// Blasts away nearby ships.
        void activate() const;

        float radius() const;

        /// Draws the special.
        void draw(float alpha) const;

    private:
        mutable float burnTimer_;
};
