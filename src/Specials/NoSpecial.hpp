#pragma once

#include "Specials/Special.hpp"


/// Special: NoSpecial.
/// Nothing at all...

class NoSpecial: public Special
{
    public:
        /// Ctor which constructs the special.
        NoSpecial(Ship* parent):
              Special(specials::All, parent, sf::String("Nothing"))
        {   }

        /// Does nothing.
        void activate() const
        {   }

        float radius() const
        {  return 0.f;  }

        /// Draws the special.
        void draw(float alpha) const;
};
