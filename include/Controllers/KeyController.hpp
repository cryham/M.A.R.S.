#pragma once

#include "Controllers/Controller.hpp"
#include "System/Key.hpp"

#include <SFML/Window.hpp>


/// A Controller which updates it's associated Ship based on keyboard events.
/// Used for local players.

class KeyController: public Controller
{
    public:
        /// Constructs a KeyController, attached to a Player.
        /// \param slave The Player, controlled by the Keyboard.
        /// \param type Should be cPlayer1 or cPlayer2.
        KeyController(Player* slave);

        /// Updates the Controller, based on the current input state.
        void update() const;

        /// Updates the Controller, based on single key events.
        void update(Key const& key)  const;

        void evaluate();
};
