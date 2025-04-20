#pragma once

#include "Interface/UiElement.hpp"


class Line: public UiElement
{
    public:
        Line(Vector2f const& begin, Vector2f const& end);

        void draw() const override;

        bool isTabable() const override
        {   return false;  }

    private:
        Vector2f begin_;
        Vector2f end_;
};

