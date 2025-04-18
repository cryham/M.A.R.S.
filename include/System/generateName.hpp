#pragma once

#include "System/Key.hpp"

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/// A namespace for genearing names.
/// It generates names for bots, the game itself and
/// stores the names for the ships.

namespace generateName 
{
    /// Returns a random bot name and its associated strength.
    /// The name is loaded from the file "botnames.txt".
    /// \param randomNumber Chooses the group of names from which the returned
    ///        name will be chosen. For bots in the same team, use the same number.
    std::pair<sf::String, int> const& bot(int randomNumber);

    /// Returns a random name for the game.
    /// For instance "Retarded Shooter" or "Rude Shooter".
    sf::String const& game();

    /// Returns a reference to a vector containing the ship names.
    /// they are loaded from the file "shipnames.txt"
    std::vector<sf::String> const& shipNames();

    /// Returns a human-readable string, containing the name of given key.
    /// The key is loaded from the current locale.
    sf::String const key(Key const& keyCode);
}

