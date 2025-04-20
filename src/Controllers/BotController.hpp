#pragma once

#include "Controllers/Controller.hpp"

#include "System/Vector2f.hpp"
#include "Teams/Job.hpp"

#include <map>

class TacticalZone;


class BotController : public Controller
{
    public:
        /// Constructs the BotController, initializing its members.
        /// \param slave The Player, controlled by this bot.
        /// \param type The type of the Controller.
        /// \param strength The individual strength of the bot. From 0 to 100.
        BotController(Player* slave, float strength);

        /// Performs the action with the highest priority.
        /// And calls evaluate twice a second.
        /*virtual*/ void update();

        void evaluate();

        void applyForJob(JobMap& jobMap);

        /// Draws some debugging stuff.
        /// Like lines, showing where the bot heads.
        void draw();

        /// Resets private members.
        /// Should be called, when a game restarts.
        void reset();

        void assignJob(Job const& job);

    private:
        // checks
        void checkAggro();
        void checkEnergy();
        void checkSpecial();
        void checkCloseEnemies();

        // team actions
        void     performJob();
        void     kickBallToEnemy();
        void     kickBallOutHome();
        void     waitForBall();
        void     attackTarget();
        void     attackAny();
        void     protectZone();
        void     escape();
        void     heal();
        void     unfreeze();
        void     getPowerUp();
        void     getControl();

        // basic actions
        void     switchSpecial();
        void     switchWeapon();
        void     charge();
        void     land();

        Ship*    target_ = nullptr;
        std::map<Ship*, float> aggroTable_;

        Job      currentJob_;

        float    weaponChangeTimer_;
        float    specialChangeTimer_;

        float lastFrameLife_;

        // helper functions
        bool     turnTo(Vector2f const& location);
        bool     moveTo(Vector2f const& location, float stopFactor, bool avoidBall = true, float minDistance = 10.f, bool goingToLand = false);
        Vector2f calcPath(Vector2f const& endPoint, bool avoidBall);
        void     shootEnemies();
        void     shootEnemy(Ship* enemyShip);
        void     shootPoint(Vector2f const& location, bool avoidTeamMembers = true);

        Vector2f nextRoutePoint_;
        TacticalZone* toCover_ = nullptr;
        const float strength_;

        //path variables
        Vector2f aimDirection_;
        Vector2f moveToPoint_;
        Vector2f nextPathPoint_;
};
