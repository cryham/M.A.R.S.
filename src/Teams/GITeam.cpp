#include "Teams/GITeam.hpp"

#include "Players/Player.hpp"
#include "SpaceObjects/ships.hpp"


void GITeam::createJobs()
{
    checkEnemies();

    for (int i=0; i < botControllers_.size(); ++i)
    {
        addJob(Job(Job::jLand, 1));
        addJob(Job(Job::jCharge, 1));
    }
}

void GITeam::checkEnemies()
{
    std::vector<Ship*> ships = ships::getShips();
    bool existAny(false);

    for (const auto& it : ships)
        if (it->getOwner()->team() != this && it->attackable())
        {
            existAny = true;
            break;
        }

    if (existAny)
        for (int i=0; i < botControllers_.size(); ++i)
            addJob(Job(Job::jAttackAny, 90));
    else
        for (int i=0; i < botControllers_.size(); ++i)
            addJob(Job(Job::jEscape, 3));
}
