#pragma once

#include "System/settings.hpp"

#include <SFML/Graphics.hpp>


/// A namespace for loading font files.

namespace font 
{
    /// Returns a const& to the SFML font.
    /// The returned font is based on the current locale.
    sf::Font* getFont(int languageID = settings::iLanguageID);
}
