#pragma once

#include "Games/games.hpp"


/// Base class for all games.
/// Provides some basic methods.

class Game
{
    public:
        /// Ctor starts a game based on the given GameType.
        /// The previous game has to be deleted before creating
        /// a new one.
        Game(games::GameType const& type);

        /// Destructor clears all game related namespaces.
        /// E.g.: ships::clear(), balls::clear(), physics::clear(),
        /// particles::clear(), spaceObjects::clear(),
        /// controllers::clear(), players::clear(), zones::clear(),
        /// decoObjects::clear(), items::clear().
        virtual ~Game();

        /// Updates the game.
        /// Has to be called every frame.
        /// Derived Games may extend this function.
        virtual void update();

        /// Draws the game.
        /// Derived Games may extend this function.
        virtual void draw() const;

        /// Restarts the game.
        /// All settings are kept. (most important: The teams aren't changed).
        /// Derived Games may extend this function.
        virtual void restart();

        /// Returns the game's GameType.
        games::GameType type() const;

        /// Returns the elapsed time since it has been created.
        float elapsedTime() const;

        bool ended() const;

        //  copy weapons and specials from ByUser
        void copyFromUser();
        void clear();

    private:
        games::GameType type_;
        float           startTime_;
        int             pointLimit_;
        bool            ended_;
};
