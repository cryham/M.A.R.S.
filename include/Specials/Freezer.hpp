#pragma once

#include "Specials/Special.hpp"


/// Special: Freezer.
/// A Freezing wave.

class Freezer: public Special
{
    public:
        /// Ctor which constructs the special.
        Freezer(Ship* parent):
              Special(specials::sFreeze, parent, sf::String("FREEZER")),
              radius_(0.f)
        {   }

        /// Freezes nearby ships.
        void activate() const;

        float radius() const;

        /// Draws the special.
        void draw(float alpha) const;

    private:
        mutable float radius_;
};
