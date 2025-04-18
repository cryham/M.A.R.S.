#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Locales/locales.hpp"


class KeyEdit: public UiElement
{
    public:
        KeyEdit (locales::LocaleType text, locales::LocaleType toolTip,
            Key* value,
            Vector2f const& topLeft, int width, int labelWidth, Color3f color = {0.7f,0.7f,0.7f});
        KeyEdit (const sf::String& text, const sf::String& toolTip,
            Key* value,
            Vector2f const& topLeft, int width, int labelWidth, Color3f color = {0.7f,0.7f,0.7f});
        ~KeyEdit ();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        Key* value_;
        Label* label_;
        sf::String toolTip_;
        int labelWidth_;
};
