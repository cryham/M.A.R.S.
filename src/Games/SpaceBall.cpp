/* SpaceBall.cpp

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

#include "Games/SpaceBall.hpp"

#include "Teams/SBTeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/ships.hpp"
#include "Players/players.hpp"
#include "Teams/teams.hpp"


SpaceBall::SpaceBall()
    :Game(games::gSpaceBall)
{
    copyFromUser();

    music::play();

    Team* myTeamL = nullptr;
    Team* myTeamR = nullptr;

    if (settings::bPlayer1teamL)
    {
        myTeamL = new SBTeam(settings::clr1Team);
        players::addPlayer(myTeamL, controllers::cPlayer1);
    }
    else if (settings::bPlayer1teamR)
    {
        myTeamR = new SBTeam(settings::clr1Team);
        players::addPlayer(myTeamR, controllers::cPlayer1);
    }

    if (settings::bPlayer2teamL)
    {
        if (!myTeamL)
            myTeamL = new SBTeam(settings::clr2Team);
        players::addPlayer(myTeamL, controllers::cPlayer2);
    }
    else if (settings::bPlayer2teamR)
    {
        if (!myTeamR)
            myTeamR = new SBTeam(settings::clr2Team);
        players::addPlayer(myTeamR, controllers::cPlayer2);
    }

    if (!myTeamR && !myTeamL)
    {
        Color3f rand = Color3f::random();
        myTeamL = new SBTeam(rand.inverted());
        myTeamR = new SBTeam(rand);
    }
    else if (!myTeamL)
        myTeamL = new SBTeam(myTeamR->color().inverted());
    else if (!myTeamR)
        myTeamR = new SBTeam(myTeamL->color().inverted());

    teams::addTeam(myTeamL);
    teams::addTeam(myTeamR);

    for (int i=0; i < settings::iBotsLeft;  ++i)  players::addPlayer(myTeamL, controllers::cBot);
    for (int i=0; i < settings::iBotsRight; ++i)  players::addPlayer(myTeamR, controllers::cBot);

    init();
}


void SpaceBall::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    Game::draw();
}

void SpaceBall::restart()
{
    Game::restart();
    init();
}


void SpaceBall::init()
{
    Home* homeL = spaceObjects::addHome(HOME_LEFT, settings::iPointLimitSB, teams::getTeamL()->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, settings::iPointLimitSB, teams::getTeamR()->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();

    balls::addBall();

    spaceObjects::populateSpace(5.f, 10.f, 4);
    ships::createTurrets();

    zones::detectTacticalZones();
    zones::createRaster(4, 3);
}
