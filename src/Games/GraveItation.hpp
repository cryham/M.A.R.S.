#pragma once

#include "Games/Game.hpp"


/// Game: GraveItation (GI).
/// InstaGib with one instantly killing weapon.

class GraveItation: public Game
{
    public:
        /// Ctor starts a new game.
        GraveItation();
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;
};
