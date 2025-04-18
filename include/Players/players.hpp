#pragma once

#include "System/Color3f.hpp"
#include "Controllers/controllers.hpp"

class Team;
class Home;
class Player;


namespace players 
{
    void addPlayer (Team* team, controllers::ControlType type, Color3f const& = Color3f::random());

    void createShips();

    void resetPlayerPoints();
    void clear();

    Player const* getPlayer1();
    Player const* getPlayer2();
}
