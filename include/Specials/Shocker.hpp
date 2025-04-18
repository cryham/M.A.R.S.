#pragma once

#include "Specials/Special.hpp"
#include "SpaceObjects/Ball.hpp"

#include <list>


/// Special: Shocker.
/// Fires shocking bolts.

class Shocker: public Special
{
    public:
        /// Ctor which constructs the special.
        Shocker(Ship* parent):
              Special(specials::sShocker, parent, sf::String("SHOCKER"))
        {   }

        /// Blasts away nearby ships.
        void activate() const;

        float radius() const;

        /// Draws the special.
        void draw(float alpha) const;

    private:
        mutable std::list<Ship*> targets_;
        mutable Ball* ballTarget_;
};
