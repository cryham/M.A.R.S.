#include "Players/BotPlayer.hpp"

#include "Controllers/controllers.hpp"
#include "System/settings.hpp"


BotPlayer::BotPlayer(std::pair<sf::String, int>const& nameStrength, Color3f const& color, int  graphic)
    :Player(controllers::cBot)
    ,name_(nameStrength.first)
    ,color_(color)
    ,graphic_(graphic)
{
    controller_ = controllers::addBotController(this,
        static_cast<float>(nameStrength.second + settings::iBotsDifficulty)*0.005f);
}
