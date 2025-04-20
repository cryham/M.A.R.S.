#pragma once

#include "Players/Player.hpp"

class BotController;
class Team;


class BotPlayer : public Player
{
    public:
        BotPlayer(std::pair<sf::String, int>const& nameStrength,
            Color3f const& color, int  graphic);

        Color3f const&     color()   const {  return color_;  }
        sf::String const&  name()    const {  return name_;  }
        int                graphic() const {  return graphic_;  }

        friend class BotController;
        friend class Team;

    private:
        sf::String  name_;
        Color3f color_;
        int graphic_;
        BotController* controller_;
};
