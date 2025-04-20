#pragma once

#include "System/Key.hpp"

#include <SFML/Window.hpp>

class Player;
class BotController;
class KeyController;


/// A namespace which controls all Ships.
/// Local Player's Ships are controlled by KeyControllers, Bots
/// are controlled by BotControllers.

namespace controllers 
{
    /// A list of all supported control types.
    enum ControlType
    {
        cBot,           ///< A bot controlled by AI.
        cPlayer1,       ///< Local player one.
        cPlayer2        ///< Local player two.
    };

    /// Updates all controllers.
    void update();

    /// Notifies KeyControllers of single key events.
    void singleKeyEvent(Key const& keyCode);

    /// Draws some debugging stuff.
    /// Like lines, showing where the bot heads.
    void draw();

    /// Adds a controller to the game.
    /// \param slave The Player, controlled by this bot.
    /// \param type The type of the Controller.
    /// \param strength The individual strength of the bot. From 0 to 100.
    BotController* addBotController(Player* slave, float strength = 1.f);
    KeyController* addKeyController(Player* slave);

    /// Resets Controllers.
    /// Should be called, when a game restarts.
    void resetBots();

    /// Deletes all Controllers.
    void clear();
}
