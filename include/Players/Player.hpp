#pragma once

#include "SpaceObjects/Ship.hpp"
#include "Players/players.hpp"
#include "Controllers/Controller.hpp"

class Team;


class Player
{
    public:
        Player(controllers::ControlType controlType);
        virtual ~Player()
        {   }

        void                      resetPoints();

        Team*                     team()    const {  return team_;  }
        Ship*                     ship()    const {  return ship_;  }
        controllers::ControlType  type()    const {  return controlType_;  }

        virtual Color3f const&    color()   const = 0;
        virtual sf::String const& name()    const = 0;
        virtual int               graphic() const = 0;

        void                      addGoal();
        void                      subGoal();

        friend class Team;
        friend class Ship;
        friend class Controller;
        friend class TabStats;
        friend class Cannon;
        friend class Turret;

    private:
        Ship* ship_ = nullptr;
        Team* team_ = nullptr;

        int points_, frags_, suicides_, deaths_, teamKills_, cannonShots_,
            goals_, selfGoals_;

        controllers::ControlType controlType_;
};
