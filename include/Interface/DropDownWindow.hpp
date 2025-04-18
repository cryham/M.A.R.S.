#pragma once

#include "Interface/UiWindow.hpp"

#include <vector>
#include <SFML/System.hpp>

class ComboBox;


class DropDownWindow: public UiWindow
{
    public:
        DropDownWindow (int width, ComboBox* parent, std::vector<sf::String> elements);

        void checkWidgets();
        void onShow();

        void reset()
        {   }

    private:
        ComboBox*                                  parent_;
        std::vector<std::pair<sf::String, bool> >  elements_;
};

