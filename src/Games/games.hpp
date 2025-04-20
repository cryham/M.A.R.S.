#pragma once


/// A namespace which handles the current game.
/// With functions of this namespace, games may be launched,
/// updated and drawn. Furthermore some information on the
/// current game can be retrieved.

namespace games 
{
    /// The different games included in MARS.
    enum GameType
    {
        gNoGame,        ///< No game is currently played (rarely used).
        gMenu,          ///< This is the game which plays in the background of the main menu.
                        ///< It's simplified TeamDeathMatch - no human players are added.
        gSpaceBall,     ///< The original M.A.R.S. GameType. A little bit like soccer:
                        ///< Each team tries to destroy the opponents home planet by dropping a huge ball on it.
        gDeathMatch,    ///< Classic Deathmatch. Smash as many opponents as possible. Be the first to reach the frag limit.
        gTeamDeathMatch,///< Classic DeathMatch, but in teams: Smash as many opponents as possible.
                        ///< Be in the team which first reaches the frag limit.
        gCannonKeep,    ///< A funny game, where both teams aim on keeping the control of gigantic weapon of mass
                        ///< destruction in order to smash the oponents home planet. The team which is the first to
                        ///< destroy the others planet will win the match.
        gGraveItation,  ///< InstaGib with only one Weapon, which kills instantly.
        gRally,         ///< Be the first to reach a goal.
        gTutorial       ///< This is the tutorial which, in fact, is a special game.
    };

    /// Updates the current game.
    /// Should be called once a frame.
    void update();

    /// Draws the current game.
    /// Should be called once a frame.
    void draw();

    /// Starts a new Game.
    /// The current game is ended before.
    /// \param type Specifies the type of the game to be launched.
    void start(GameType const& type);

    /// Restarts the current Game.
    /// All teams are kept.
    void restart();

    /// Returns false, when there is currently a transition from one game to another.
    bool active();

    bool ended();

    /// Returns the GameType of the current Game.
    GameType type();

    /// Returns the duration of the current Game.
    float elapsedTime();
}
