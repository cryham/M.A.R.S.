#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Locales/locales.hpp"


class Checkbox: public UiElement
{
    public:
        Checkbox (const sf::String& text, const sf::String& toolTip,
            bool* value, Vector2f const& topLeft, int width, Color3f color = {0.7f,0.7f,0.7f});
        Checkbox (locales::LocaleType text, locales::LocaleType toolTip,
            bool* value, Vector2f const& topLeft, int width, Color3f color = {0.7f,0.7f,0.7f});
        ~Checkbox ();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        bool* value_;
        Label* label_;
        sf::String toolTip_;
};
