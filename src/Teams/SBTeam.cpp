#include "Teams/SBTeam.hpp"

#include "Items/PowerUp.hpp"
#include "Items/items.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"

#include <list>


void SBTeam::createJobs()
{
    checkBall();
    checkEnemies();
    checkPowerUps();

     for (int i=0; i < botControllers_.size(); ++i)
     {
        addJob(Job(Job::jLand, 20));
        addJob(Job(Job::jCharge, 20));
    }
}

void SBTeam::checkEnemies()
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
            addJob(Job(Job::jAttackAny, 5));
}

void SBTeam::checkPowerUps()
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
                case items::puFuel:     addJob(Job(Job::jGetPUFuel,    30, &powerUpLocations_.back()));  break;
                case items::puHealth:   addJob(Job(Job::jGetPUHealth,  30, &powerUpLocations_.back()));  break;
                case items::puReverse:
                    if (existAny)       addJob(Job(Job::jGetPUReverse, 40, &powerUpLocations_.back()));  break;
                case items::puShield:   addJob(Job(Job::jGetPUShield,  30, &powerUpLocations_.back()));  break;
                default: if (existAny)  addJob(Job(Job::jGetPUSleep,   40, &powerUpLocations_.back()));  break;
            }
        }
    }
}

void SBTeam::checkBall()
{
    Ball* ball = balls::getBall();
    if (ball)
    {
        if (!ball->isVisible())
        {
            int waitCount(settings::iBotsDifficulty * (botControllers_.size()+1) / 200);
            for (int i=0; i < waitCount; ++i)
                addJob(Job(Job::jWaitForBall, 5, ball));
        }else
        {
            int ballZone(zones::isInside(this, *ball));
            switch (ballZone)
            {
                case OWN_HOME:
                    for (int i=0; i<botControllers_.size(); ++i)
                        addJob(Job(Job::jKickOutHome, 90, ball));
                    break;

                case OWN_TEAM:
                {
                    std::map<float, TacticalZone*> zones(zones::toProtect(this));
                    auto currentZone = zones.begin();
                    int protectJobs(botControllers_.size()*0.5);

                    while (protectJobs > 0)
                    {
                        for (int i=0; i<(protectJobs+1)*0.5; ++i)
                            addJob(Job(Job::jProtectZone, 30,  currentZone->second));

                        protectJobs /= 2;
                        if (++currentZone == zones.end())
                            currentZone = zones.begin();
                    }
                    for (int i=botControllers_.size()*0.5f; i<botControllers_.size(); ++i)
                        addJob(Job(Job::jKickToEnemy, 60, ball));
                    
                    for (int i=0; i<botControllers_.size()*0.5; ++i)
                        addJob(Job(Job::jKickOutHome, 40, ball));

                    break;
                }
                default:
                {
                    std::map<float, TacticalZone*> zones(zones::toProtect(this));
                    auto currentZone = zones.begin();
                    int protectJobs(botControllers_.size()*0.4);

                    while (protectJobs > 0)
                    {
                        for (int i=0; i<(protectJobs+1)*0.5; ++i)
                            addJob(Job(Job::jProtectZone, 20,  currentZone->second));

                        protectJobs /= 2;
                        if (++currentZone == zones.end())
                            currentZone = zones.begin();
                    }
                    for (int i=0; i < botControllers_.size()*0.6f; ++i)
                        addJob(Job(Job::jKickToEnemy, 60, ball));
                }
            }
        }
    }
}
