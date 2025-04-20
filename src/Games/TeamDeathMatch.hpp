#pragma once

#include "Games/Game.hpp"


/// Game: TeamDeathMatch (TDM).
/// Classic DeathMatch, but in teams: Smash as many opponents as possible.
/// Be in the team which first reaches the frag limit.

class TeamDeathMatch : public Game
{
    public:
        /// Ctor starts a new game.
        TeamDeathMatch();
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;
};

