#pragma once

#include "Interface/UiElement.hpp"

#include <vector>


class VerticalSlider : public UiElement
{
    public:
        VerticalSlider (float* value, float min, float max,
            Vector2f const& topLeft, int height);

        void mouseLeft(bool down) override;
        void mouseMoved(Vector2f const& position) override;

        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

    private:
        float* value_;
        float minValue_, maxValue_;
};
