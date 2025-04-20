#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"

class UiWindow;


class ColorPicker : public UiElement
{
    public:
        ColorPicker (const sf::String& text, Color3f* value,
            Vector2f const& topLeft, int width, int labelWidth=185);
        ~ColorPicker ();

        void mouseMoved(Vector2f const& position) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        friend class ColorPickerWindow;

    private:
        UiWindow* colorWindow_ = nullptr;

        Color3f* currentValue_ = nullptr;
        Label* label_ = nullptr;

        int labelWidth_;
        bool opened_;
};
