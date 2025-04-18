#pragma once

#include "Specials/Special.hpp"


/// Special: Blast.
/// A blast wave.

class Blast: public Special
{
    public:
        /// Ctor which constructs the special.
        Blast(Ship* parent):
              Special(specials::sBlast, parent, sf::String("BLAST")),
              radius_(0.f)
        {   }

        /// Blasts away nearby ships.
        void activate() const;

        float radius() const;

        /// Draws the special.
        void draw(float alpha) const;

    private:
        mutable float radius_;
};
