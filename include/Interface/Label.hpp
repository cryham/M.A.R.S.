#pragma once

#include "Interface/UiElement.hpp"
#include "System/Color3f.hpp"


class Label: public UiElement
{
    public:
        Label (const sf::String& text, int textAlign,
            Vector2f const& topLeft, float fontSize = 12.f,
            Color3f color = Color3f(0.7f,0.7f,0.7f),
            bool interactive = true, sf::Font* font = nullptr);

        void mouseMoved(Vector2f const& position) override;

        void draw() const override;

        bool isTabable() const override
        {   return false;  }

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        sf::String text_;
        sf::Font*  font_;
        int textAlign_;
        float fontSize_;
        Color3f color_;
        bool interactive_;
};
