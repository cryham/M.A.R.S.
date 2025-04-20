#pragma once

#include "Games/Game.hpp"


/// Game: DeathMatch (DM).
/// Classic Deathmatch. Smash as many opponents as possible.
/// Be the first to reach the frag limit.

class DeathMatch : public Game
{
    public:
        /// Ctor starts a new game.
        DeathMatch();
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;
};
