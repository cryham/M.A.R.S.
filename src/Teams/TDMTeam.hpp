#pragma once

#include "Teams/Team.hpp"


class TDMTeam: public Team
{
    public:
        TDMTeam(Color3f const& color = Color3f::random()):
            Team(color)
        {   }

    private:
        void createJobs();

        void checkEnemies();
        void checkPowerUps();

        std::vector<Vector2f> powerUpLocations_;
};
