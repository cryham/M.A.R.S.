#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"

class UiWindow;


class LanguageButton : public UiElement
{
    public:
        LanguageButton (const sf::String& text, Vector2f const& topLeft, int width, int labelWidth=185);
        ~LanguageButton ();

        void mouseMoved(Vector2f const& position) override;
        void mouseWheelMoved(Vector2f const& position, int delta) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        sf::String currentValue_;
        Label* label_;
        int labelWidth_;
        bool opened_;
};
