#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Interface/RadioGroup.hpp"

class RadioGroup;


class RadioButton : public UiElement
{
    public:
        RadioButton(const sf::String& text, const sf::String& toolTip, bool* value,
            Vector2f const& topLeft, int width, bool offSwitchable = false);
        ~RadioButton();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        friend class RadioGroup;

    private:
        bool* value_;
        Label* label_;
        bool offSwitchable_;
        sf::String toolTip_;
};
