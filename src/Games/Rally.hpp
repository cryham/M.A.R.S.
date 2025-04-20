#pragma once

#include "Games/Game.hpp"

class Track;


/// Game: Rally (RLY).
/// Be the first to reach a goal.

class Rally : public Game
{
    public:
        /// Ctor starts a new game.
        Rally();
        ~Rally();
        
        void init();

        /// Draws the game.
        void draw() const override;

        /// Restarts the game.
        void restart() override;

    private:
        Track* track_;
};
