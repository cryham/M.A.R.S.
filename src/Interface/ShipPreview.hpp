#pragma once

#include "Interface/UiElement.hpp"
#include "System/Color3f.hpp"


class ShipPreview : public UiElement
{
    public:
        ShipPreview (Color3f* color, Color3f* teamColor,
            int* graphic, Vector2f const& topLeft);

        void draw() const override;

        bool isTabable() const override
        {   return false;  }

    private:
        Color3f* color_;
        Color3f* teamColor_;
        int*     graphic_;
};
