#include "Controllers/KeyController.hpp"

#include "System/window.hpp"
#include "System/settings.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"


KeyController::KeyController(Player* slave)
    :Controller(slave)
{   }

void KeyController::update() const
{
    if (type_ == controllers::cPlayer1)
    {
        slaveUp   (window::isKeyDown(settings::key1up));
        slaveDown (window::isKeyDown(settings::key1down));
        slaveBoost(window::isKeyDown(settings::key1boost));

        slaveLeft (window::isKeyDown(settings::key1left));
        slaveRight(window::isKeyDown(settings::key1right));
        
        slaveFire (window::isKeyDown(settings::key1fire));
        slaveSpecial (window::isKeyDown(settings::key1SpecialKey));
    }
    else if (type_ == controllers::cPlayer2)
    {
        slaveUp   (window::isKeyDown(settings::key2up));
        slaveDown (window::isKeyDown(settings::key2down));
        slaveBoost(window::isKeyDown(settings::key2boost));

        slaveLeft (window::isKeyDown(settings::key2left));
        slaveRight(window::isKeyDown(settings::key2right));

        slaveFire (window::isKeyDown(settings::key2fire));
        slaveSpecial (window::isKeyDown(settings::key2SpecialKey));
    }
}

void KeyController::update(Key const& key) const
{
    if (type_ == controllers::cPlayer1 && key.strength_ == 100)
    {
        if      (key == settings::key1up)    slaveUp();
        else if (key == settings::key1down)  slaveDown();
        else if (key == settings::key1boost) slaveBoost();

        else if (key == settings::key1left)  slaveLeft();
        else if (key == settings::key1right) slaveRight();
        
        else if (key == settings::key1fire)  slaveFire();
        else if (key == settings::key1SpecialKey)  slaveSpecial();

        else if (key == settings::key1prev)  slavePrev();
        else if (key == settings::key1next)  slaveNext();
    }
    else if (type_ == controllers::cPlayer2 && key.strength_ == 100)
    {
        if      (key == settings::key2up)    slaveUp();
        else if (key == settings::key2down)  slaveDown();
        else if (key == settings::key2boost) slaveBoost();

        else if (key == settings::key2left)  slaveLeft();
        else if (key == settings::key2right) slaveRight();
        
        else if (key == settings::key2fire)  slaveFire();
        else if (key == settings::key2SpecialKey)  slaveSpecial();

        else if (key == settings::key2prev)  slavePrev();
        else if (key == settings::key2next)  slaveNext();
    }
}


void KeyController::evaluate()
{
    if (std::max(100 - ship()->getLife(), 100 - ship()->getFuel()) > 30)
    {
        slave_->team()->addJob(Job(Job::jHeal, std::max(100 - ship()->getLife(), 100 - ship()->getFuel()), ship()));
        slave_->team()->addJob(Job(Job::jHeal, std::max(100 - ship()->getLife(), 100 - ship()->getFuel()), ship()));
    }
    if (ship()->frozen_ > 0)
    {
        slave_->team()->addJob(Job(Job::jUnfreeze, 90, ship()));
        slave_->team()->addJob(Job(Job::jUnfreeze, 90, ship()));
        slave_->team()->addJob(Job(Job::jUnfreeze, 90, ship()));
    }
}
