#pragma once

#include <SFML/System.hpp>


struct Locale
{
    Locale():
        name_("NULL"),
        fileName_("NULL"),
        // font_("Comfortaa-Regular.ttf"),
        font_("DejaVuSans.ttf"),
        author_(""),
        LTR_(true)
    {   }

    sf::String name_;
    sf::String fileName_;
    sf::String font_;
    sf::String author_;
    bool       LTR_;
};
