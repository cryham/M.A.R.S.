#pragma once

#include "Games/Game.hpp"


/// Game: MenuGame.
/// This is the game which plays in the background of the main menu.
/// It's a little bit simplified TeamDeathMatch - no human players are added.

class MenuGame: public Game
{
    public:
        /// Ctor starts a new game.
        MenuGame();

        /// Restarts the game.
        void restart();
};

