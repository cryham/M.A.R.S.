#pragma once

#include "Teams/Team.hpp"


class CKTeam : public Team
{
    public:
        CKTeam(Color3f const& color = Color3f::random()):
            Team(color)
        {   }

    private:
        void createJobs();

        void checkEnemies();
        void checkPowerUps();
        void checkControl();

        std::vector<Vector2f> powerUpLocations_;
};
