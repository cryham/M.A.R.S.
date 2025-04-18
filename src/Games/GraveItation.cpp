/* GraveItation.cpp

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

#include "Games/GraveItation.hpp"

#include "Teams/GITeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Players/players.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "Teams/teams.hpp"


GraveItation::GraveItation()
    :Game(games::gGraveItation)
{
    clear();
    settings::bEnabledWeapons[weapons::wInsta] = true;

    music::play();

    Team* myTeamL = nullptr;
    Team* myTeamR = nullptr;

    if (settings::bPlayer1teamL)
    {
        myTeamL = new GITeam(settings::clr1Team);
        players::addPlayer(myTeamL, controllers::cPlayer1);
    }
    else if (settings::bPlayer1teamR)
    {
        myTeamR = new GITeam(settings::clr1Team);
        players::addPlayer(myTeamR, controllers::cPlayer1);
    }

    if (settings::bPlayer2teamL)
    {
        if (!myTeamL)
            myTeamL = new GITeam(settings::clr2Team);
        players::addPlayer(myTeamL, controllers::cPlayer2);
    }
    else if (settings::bPlayer2teamR)
    {
        if (!myTeamR)
            myTeamR = new GITeam(settings::clr2Team);
        players::addPlayer(myTeamR, controllers::cPlayer2);
    }

    if (!myTeamR && !myTeamL)
    {
        Color3f rand = Color3f::random();
        myTeamL = new GITeam(rand.inverted());
        myTeamR = new GITeam(rand);

    }
    else if (!myTeamL)
        myTeamL = new GITeam(myTeamR->color().inverted());
    else if (!myTeamR)
        myTeamR = new GITeam(myTeamL->color().inverted());

    teams::addTeam(myTeamL);
    teams::addTeam(myTeamR);

    for (int i=0; i < settings::iBotsLeft;  ++i)  players::addPlayer(myTeamL, controllers::cBot);
    for (int i=0; i < settings::iBotsRight; ++i)  players::addPlayer(myTeamR, controllers::cBot);

    init();
}

void GraveItation::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    Game::draw();
}

void GraveItation::restart()
{
    Game::restart();
    init();
}


void GraveItation::init()
{
    Home* homeL = spaceObjects::addHome(HOME_LEFT, 100, teams::getTeamL()->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, 100, teams::getTeamR()->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();

    spaceObjects::populateSpace(25.f, 5.f, 2);

    zones::createRaster(4,3);
}
