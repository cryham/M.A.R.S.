#include "Teams/DMTeam.hpp"

#include "Teams/teams.hpp"
#include "Players/Player.hpp"
#include "Items/items.hpp"
#include "Items/PowerUp.hpp"
#include "SpaceObjects/ships.hpp"
#include "Games/games.hpp"


void DMTeam::createJobs()
{
    checkEnemies();
    checkPowerUps();

    for (int i=0; i < botControllers_.size(); ++i)
    {
        addJob(Job(Job::jLand, 4));
        addJob(Job(Job::jCharge, 4));
    }
}

void DMTeam::checkEnemies()
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
            addJob(Job(Job::jAttackAny, 60));
    else
        for (int i=0; i < botControllers_.size(); ++i)
            addJob(Job(Job::jEscape, 6));
}

void DMTeam::checkPowerUps()
{
    std::vector<Ship*> ships = ships::getShips();
    bool existAny(false);

    for (const auto& it : ships)
        if (it->getOwner()->team() != this && it->attackable())
        {
            existAny = true;
            break;
        }

    powerUpLocations_.clear();
    const auto& powerUps = items::getPowerUps();
    powerUpLocations_.reserve(powerUps.size());
    for (const auto& it : powerUps)
    {
        if (!it->isCollected())
        {
            powerUpLocations_.push_back(it->location());
            switch (it->type())
            {
                case items::puFuel:     addJob(Job(Job::jGetPUFuel,    70, &powerUpLocations_.back()));  break;
                case items::puHealth:   addJob(Job(Job::jGetPUHealth,  70, &powerUpLocations_.back()));  break;
                case items::puReverse:
                    if (existAny)       addJob(Job(Job::jGetPUReverse, 70, &powerUpLocations_.back()));  break;
                case items::puShield:   addJob(Job(Job::jGetPUShield,  70, &powerUpLocations_.back()));  break;
                default: if (existAny)  addJob(Job(Job::jGetPUSleep,   70, &powerUpLocations_.back()));  break;
            }
        }
    }
}
