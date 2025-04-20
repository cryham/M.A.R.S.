#pragma once

#include "DecoObjects/DecoObject.hpp"

class Ship;


/// A rotating ring which can be attached to a Ship.
/// Human controlled Ships are highlighed to make it
/// easier to see the Ship

class ShipHighlight : public DecoObject
{
    public:
        ShipHighlight(Ship* ship): ship_(ship)
        {   }

        void draw() const override;

    private:
        void draw(Vector2f const& location, float scale, float alpha) const;

        Ship* ship_;
};
