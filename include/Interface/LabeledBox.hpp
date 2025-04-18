#pragma once

#include "Interface/UiElement.hpp"

class Label;


class LabeledBox: public UiElement
{
    public:
        LabeledBox(const sf::String& text, Vector2f const& topLeft, int width, int height);

        ~LabeledBox();

        void draw() const override;

        bool isTabable() const override
        {   return false;  }

    private:
        Label* label_ = nullptr;
};


