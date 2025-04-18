#include "Players/players.hpp"

#include "Players/LocalPlayer.hpp"
#include "Players/BotPlayer.hpp"
#include "System/settings.hpp"
#include "System/generateName.hpp"
#include "Teams/Team.hpp"
#include "SpaceObjects/Home.hpp"
#include "defines.hpp"

#include <climits>


namespace players 
{
    namespace
	{
        std::vector<Player*> allPlayers_;
        Player* player1_;
        Player* player2_;
        bool initialized_(false);

        void initLocalPlayers()
        {
            player1_ = new LocalPlayer(controllers::cPlayer1);
            player2_ = new LocalPlayer(controllers::cPlayer2);
            initialized_ = true;
        }
    }


    void addPlayer (Team* team, controllers::ControlType type, Color3f const& color)
    {
        switch (type)
        {
            case controllers::cPlayer1:
                if (!initialized_)
                    initLocalPlayers();
                team->addMember(player1_);
                allPlayers_.push_back(player1_);
                break;

            case controllers::cPlayer2:
                if (!initialized_)
                    initLocalPlayers();
                team->addMember(player2_);
                allPlayers_.push_back(player2_);
                break;

            default:
                Player* bot = new BotPlayer(generateName::bot(
                    ((long)team % INT_MAX) / 97), color, rand() % SHIP_GRAPHICS_COUNT+1);
                team->addMember(bot);
                allPlayers_.push_back(bot);
        }
    }

    void createShips()
    {
        // temporary list of all homes
        const auto& homes = spaceObjects::getHomes();
        // temporary lists of all inhabitants of all
        for (const auto& home : homes)
        {
            std::vector<Player*> inhabitants;
            for (const auto& playIt : allPlayers_)
            {
                if (playIt->team()->home() == home)
                    inhabitants.push_back(playIt);
            }
            home->createShips(inhabitants);
        }
    }

    Player const* getPlayer1()
    {
        return player1_;
    }

    Player const* getPlayer2()
    {
        return player2_;
    }

    void resetPlayerPoints()
    {
        for (auto& it : allPlayers_)
            it->resetPoints();
    }

    void clear()
    {
        for (auto& it : allPlayers_)
            delete it;
        allPlayers_.clear();
        initialized_ = false;
    }
}
