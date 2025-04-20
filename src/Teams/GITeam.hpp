#pragma once

#include "Teams/Team.hpp"


class GITeam : public Team
{
    public:
        GITeam(Color3f const& color = Color3f::random()):
            Team(color)
        {   }

    private:
        void createJobs();

        void checkEnemies();
};
