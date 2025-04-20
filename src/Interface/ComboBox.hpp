#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Locales/locales.hpp"

class UiWindow;


class ComboBox : public UiElement
{
    public:
        ComboBox (locales::LocaleType text, locales::LocaleType toolTip,
            sf::String* value, std::vector<sf::String> const& values,
            Vector2f const& topLeft, int width, int labelWidth = 185);
        ComboBox (const sf::String& text, const sf::String& toolTip,
            sf::String* value, std::vector<sf::String> const& values,
            Vector2f const& topLeft, int width, int labelWidth = 185);
        ~ComboBox ();

        void mouseMoved(Vector2f const& position) override;
        void mouseWheelMoved(Vector2f const& position, int delta) override;
        void mouseLeft(bool down) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

        friend class DropDownWindow;

    private:
        UiWindow* dropBox_ = nullptr;

        sf::String* currentValue_ = nullptr;
        std::vector<sf::String> values_;
        Label* label_ = nullptr;
        int labelWidth_;
        bool opened_;
        sf::String toolTip_;
};
