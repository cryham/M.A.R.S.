#pragma once

#include "Teams/Team.hpp"


class SBTeam: public Team
{
    public:
        SBTeam(Color3f const& color = Color3f::random()):
            Team(color)
        {   }

    private:
        void createJobs();
        void checkPowerUps();
        void checkEnemies();
        void checkBall();

        std::vector<Vector2f> powerUpLocations_;
};
