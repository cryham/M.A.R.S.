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
    weaponsClear();
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
    spaceObjects::addAsteroids();

    zones::createRaster(4,3);
}
