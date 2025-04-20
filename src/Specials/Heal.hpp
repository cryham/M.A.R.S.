#pragma once

#include "Specials/Special.hpp"


/// Special: Heal.
/// A healing wave.

class Heal: public Special
{
    public:
        /// Ctor which constructs the special.
        Heal(Ship* parent):
              Special(specials::sHeal, parent, sf::String("HEAL")),
              radius_(0.f)
        {   }

        /// Heals nearby friends.
        void activate() const;

        float radius() const;

        /// Draws the special.
        void draw(float alpha) const;

    private:
        mutable float radius_;
};
