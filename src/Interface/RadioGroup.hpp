#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/RadioButton.hpp"

#include <vector>

class RadioButton;


class RadioGroup : public UiElement
{
    public:
        RadioGroup();
        ~RadioGroup();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        bool tabNext() override;
        bool tabPrevious() override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        void draw() const override;

        void allOff();

        void addRadioButton(RadioButton* toBeAdded);

    private:
        std::vector<RadioButton*> radioButtons_;
        RadioButton* focusedButton_;
};
