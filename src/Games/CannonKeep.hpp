#pragma once

#include "Games/Game.hpp"


/// Game: CannonKeep (CK).
/// A funny game, where both teams aim on keeping the control of
/// gigantic weapon of mass destruction in order to smash the
/// oponents home planet. The team which is the first to destroy
/// the others planet will win the match.

class CannonKeep : public Game
{
    public:
        /// Ctor starts a new game.
        CannonKeep();
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;
};

