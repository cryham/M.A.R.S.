#pragma once

#include "System/Color3f.hpp"
#include "Controllers/controllers.hpp"

class Team;
class Home;
class Player;


namespace teams 
{
    Team* addTeam(Team* newTeam);

    void assignHomes(Home* home);
    void assignHomes(Home* homeL, Home* homeR);

    void update();

    void assignZones();

    void createShips();

    void resetTeamPoints();
    void clear();

    Team   const* getTeamL();
    Team   const* getTeamR();
    std::vector<Team*> const& getAllTeams();
    Team   const*             getEnemy(Team const* checker);

    int getFirstPoints();
    int getSecondPoints();
}


