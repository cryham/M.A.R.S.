/* Slider.hpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"
#include "Locales/locales.hpp"

#include <vector>


class Slider: public UiElement
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
