#pragma once

#include "System/Color3f.hpp"
#include "Controllers/controllers.hpp"
#include "Zones/zones.hpp"
#include "Teams/Job.hpp"

class Player;
class Home;
class BotController;
class KeyController;


class Team
{
    public:
        Team(Color3f const& color);
        virtual ~Team()
        {   }

        void update();

        void addMember(Player* player);
        void setHome(Home* home);

        void addJob(Job const& job);

        std::vector<Player*> const& members()   const {  return members_;  }
        Home                 const* home()      const {  return home_;  }
        Color3f              const& color()     const {  return color_;  }
        int                         points()    const {  return points_;  }
        int                         victories() const {  return victories_;  }

        void                        addStars()  const;
        void                        addPoint()  const;
        void                        subtractPoint() const;
        void                        addVictory()    const;
        void                        resetPoints()   const;

        friend short zones::isInside(Team* checker, SpaceObject const& toBeChecked);
        friend std::map<float, TacticalZone*> const zones::toProtect(Team* checker);

    protected:
        virtual void createJobs() = 0;
        std::vector<BotController*> botControllers_;
        std::vector<KeyController*> keyControllers_;

    private:
        void evaluate();

        float evaluationTimer_;
        std::vector<Player*> members_;
        
        JobMap jobMap_;

        Home* home_ = nullptr;
        Color3f color_;
        Zone* homeZone_ = nullptr;
        Zone* teamZone_ = nullptr;
        mutable int victories_;
        mutable int points_;
};
