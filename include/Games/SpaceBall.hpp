#pragma once

#include "Games/Game.hpp"


/// Game: SpaceBall (SB).
/// The original M.A.R.S. GameType. A little bit like soccer: Each team tries to destroy
/// the opponents home planet by dropping a huge ball on it.

class SpaceBall: public Game
{
    public:
        /// Ctor starts a new game.
        SpaceBall();
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;
};
