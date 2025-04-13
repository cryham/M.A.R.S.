/* KeyController.cpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

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
