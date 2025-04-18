#include "Teams/Team.hpp"

#include "Zones/zones.hpp"
#include "Players/Player.hpp"
#include "Players/BotPlayer.hpp"
#include "Players/LocalPlayer.hpp"
#include "SpaceObjects/Home.hpp"
#include "Controllers/KeyController.hpp"
#include "Games/games.hpp"
#include "Controllers/BotController.hpp"
#include "System/settings.hpp"
#include <set>


Team::Team(Color3f const& color):
    evaluationTimer_(0.f),
    color_(color),
    victories_(0),
    points_(0)
{   }

void Team::update()
{
    evaluationTimer_ += timer::frameTime();
    if (evaluationTimer_ > 0.2f)
    {   evaluationTimer_ = 0.f;
        evaluate();
    }
}

void Team::addMember(Player* player)
{
    members_.push_back(player);
    player->team_ = this;

    if (player->type() == controllers::cBot)
    {
        BotPlayer* bot = dynamic_cast<BotPlayer*>(player);
        if (bot)
            botControllers_.push_back(bot->controller_);
    }else
    {
        LocalPlayer* localPlayer = dynamic_cast<LocalPlayer*>(player);
        if (localPlayer)
            keyControllers_.push_back(localPlayer->controller_);
    }
}

void Team::setHome(Home* home)
{
    home_ = home;
    homeZone_ = zones::addHomeZone(home->location());
    teamZone_ = zones::addTeamZone(home->location());
}

void Team::addJob(Job const& job)
{
    jobMap_.insert(std::make_pair(job, std::multimap<short, BotController*> ()));
}

void Team::resetPoints() const
{
    points_ = 0;
}

void Team::addPoint() const
{
    ++points_;
}

void Team::subtractPoint() const
{
    --points_;
}

void Team::addVictory() const
{
    ++victories_;
}

void Team::addStars() const
{
    for (const auto& it : members_)
        ++it->ship()->fragStars_;
}

void Team::evaluate()
{
    jobMap_.clear();

    if (botControllers_.size() > 0 && games::elapsedTime() > settings::iCountDown)
    {
        createJobs();

        for (auto& it : botControllers_)
            it->evaluate();

        for (auto& it : keyControllers_)
            it->evaluate();

        for (auto& it : botControllers_)
            it->applyForJob(jobMap_);

        std::set<BotController*> unemployedBots(botControllers_.begin(), botControllers_.end());
        bool botsLeft(true);

        while (botsLeft)
        {
            JobMap::iterator mostWantedJob;
            BotController* mostWanting = nullptr;
            short highestDesire(0);

            for (auto it = jobMap_.begin(); it != jobMap_.end(); ++it)
            {
                auto bot = it->second.rbegin();
                while (bot != it->second.rend() &&
                    unemployedBots.find(bot->second) == unemployedBots.end())
                    ++bot;
                
                if (bot != it->second.rend() && bot->first > highestDesire)
                {
                    highestDesire = bot->first;
                    mostWantedJob = it;
                    mostWanting   = bot->second;
                }
            }

            if (mostWanting)
            {
                unemployedBots.erase(mostWanting);
                mostWanting->assignJob(mostWantedJob->first);
                jobMap_.erase(mostWantedJob);
            }
            else
                botsLeft = false;
        }

        for (auto& it : unemployedBots)
            it->assignJob(Job(Job::jLand, 10));
    }
}
