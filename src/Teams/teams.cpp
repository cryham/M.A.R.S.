#include "Teams/teams.hpp"

#include "Teams/Team.hpp"
#include "SpaceObjects/Home.hpp"

#include <climits>


namespace teams
{
    namespace
    {
        std::vector<Team*> allTeams_;
    }

    Team* addTeam(Team* newTeam)
    {
        allTeams_.push_back(newTeam);
        return newTeam;
    }

    void assignHomes(Home* home)
    {
        if (allTeams_.size() > 0)
            for (auto& it : allTeams_)
                it->setHome(home);
        else
            std::cout << "Cant assign Home Planet! No Teams are specified!\n";
    }

    void assignHomes(Home* homeL, Home* homeR)
    {
        if (allTeams_.size() == 2)
        {
            allTeams_[0]->setHome(homeL);
            allTeams_[1]->setHome(homeR);
        }else
            std::cout << "Cant assign two Home Planets! There have to be exactly two Teams specified!\n";
    }

    void update()
    {
        for (auto& it : allTeams_)
            it->update();
    }

    Team const* getTeamL()
    {
        return allTeams_[0];
    }

    Team const* getTeamR()
    {
        return allTeams_[1];
    }

    std::vector<Team*> const& getAllTeams()
    {
        return allTeams_;
    }

    Team const* getEnemy(Team const* checker)
    {
        return checker == allTeams_[0] ? allTeams_[1] : allTeams_[0];
    }

    int getFirstPoints()
    {
        int highest(INT_MIN);
        for (auto& it : allTeams_)
            if (it->points() > highest)
                highest = it->points();
        return highest;
    }

    int getSecondPoints()
    {
        int first (INT_MIN);
        int second(INT_MIN);

        for (auto& it : allTeams_)
            if (it->points() >= first)
            {
                second = first;
                first  = it->points();
            }
            else if (it->points() > second)
            {
                second = it->points();
            }
        if (second == INT_MIN)
            second = 0;
        return second;
    }

    void resetTeamPoints()
    {
        for (auto& it : allTeams_)
            it->resetPoints();
    }

    void clear()
    {
        for (auto& it : allTeams_)
            delete it;
        allTeams_.clear();
    }
}
