#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Interface/VerticalSlider.hpp"

#include <vector>


class TextBox: public UiElement
{
    public:
        TextBox (const sf::String& text,
            Vector2f const& topLeft, int width, int height,
            Color3f const& color = Color3f(0.7f, 0.7f, 0.7f));
        ~TextBox();

        void mouseMoved(Vector2f const& position);
        void mouseWheelMoved(Vector2f const& position, int delta);
        void mouseLeft(bool down);

        void draw () const;

        bool isTabable() const
        {   return false;  }

    private:
        Color3f color_;
        std::vector<sf::String> texts_;
        VerticalSlider* slider_ = nullptr;
        mutable float position_;
        mutable float scrollSpeed_;
};
