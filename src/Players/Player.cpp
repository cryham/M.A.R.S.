#include "Players/Player.hpp"
#include "Controllers/controllers.hpp"


Player::Player(controllers::ControlType controlType):
    points_(0),
    frags_(0),
    suicides_(0),
    deaths_(0),
    teamKills_(0),
    cannonShots_(0),
    goals_(0),
    selfGoals_(0),
    controlType_(controlType)
{   }

void Player::resetPoints()
{
    points_ = 0;
    frags_ = 0;
    suicides_ = 0;
    deaths_ = 0;
    teamKills_ = 0;
    cannonShots_ = 0;
    goals_ = 0;
    selfGoals_ = 0;
}

void Player::addGoal()
{
    ++goals_;
    points_ += 10;
}

void Player::subGoal()
{
    --selfGoals_;
    points_ -= 5;
}
