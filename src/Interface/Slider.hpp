#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Locales/locales.hpp"

#include <vector>


class Slider : public UiElement
{
    public:
        static std::vector<sf::String> None;

        Slider (locales::LocaleType text, locales::LocaleType toolTip,
            int* value, int minValue, int maxValue, int step,
            Vector2f const& topLeft, int width, int labelWidth = 185,
            bool showValue = false,
            std::vector<sf::String> const& sliderNames = None,
            std::string format = {"%.0f"}, float divBy = 1.f);

        Slider (const sf::String& text, const sf::String& toolTip,
            int* value, int minValue, int maxValue, int step,
            Vector2f const& topLeft, int width, int labelWidth = 185,
            bool showValue = false,
            std::vector<sf::String> const& sliderNames = None,
            std::string format = {"%.0f"}, float divBy = 1.f);
        ~Slider ();

        void mouseLeft(bool down) override;
        void mouseMoved(Vector2f const& position) override;
        void mouseWheelMoved(Vector2f const& position, int delta) override;
        void keyEvent(bool down, Key const& key) override;

        void draw() const override;

        void setFocus(UiElement* toBeFocused, bool isPrevious) override;
        void clearFocus() override;

    private:
        int* value_;
        int minValue_, maxValue_, step_;
        
        Label* label_;
        int labelWidth_;
        bool showValue_;

        std::string format_;  // value format: %4.2f, etc.
        float divBy_;  // value is divided by this
        
        std::vector<sf::String> sliderNames_;
        sf::String toolTip_;
};
