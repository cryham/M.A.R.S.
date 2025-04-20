#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Media/text.hpp"


class Button: public UiElement
{
    public:
        Button (const sf::String& text, const sf::String& toolTip, bool* key,
            Vector2f const& topLeft, int width, int height,
            int align = TEXT_ALIGN_CENTER, sf::Font* font = nullptr);
        ~Button ();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        bool* key_;
        Label* label_;
        sf::String toolTip_;
};
