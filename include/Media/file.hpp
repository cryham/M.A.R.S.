#pragma once

#include <SFML/System.hpp>
#include <string>
#include <vector>

/// A namespace for UTF-8 encoded text file handling.
/// It contains function which work with
/// UTF-8 encoded text files.

namespace file 
{
    /// Loads an UTF-8 encoded text file.
    /// The lines of this file are stored in a std::vector of SFML-Strings.
    /// Comments (//) and empty lines in this file will be ignored.
    bool load(std::string fileName, std::vector<sf::String>& strings);
}
