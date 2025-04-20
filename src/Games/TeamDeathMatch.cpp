#include "Games/TeamDeathMatch.hpp"

#include "SpaceObjects/ships.hpp"
#include "Teams/TDMTeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Players/players.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "Teams/teams.hpp"


TeamDeathMatch::TeamDeathMatch()
    :Game(games::gTeamDeathMatch)
{
    weaponsFromUser();

    music::play();

    Team* myTeamL = nullptr;
    Team* myTeamR = nullptr;

    if (settings::bPlayer1teamL)
    {
        myTeamL = new TDMTeam(settings::clr1Team);
        players::addPlayer(myTeamL, controllers::cPlayer1);
    }
    else if (settings::bPlayer1teamR)
    {
        myTeamR = new TDMTeam(settings::clr1Team);
        players::addPlayer(myTeamR, controllers::cPlayer1);
    }

    if (settings::bPlayer2teamL)
    {
        if (!myTeamL) myTeamL = new TDMTeam(settings::clr2Team);
        players::addPlayer(myTeamL, controllers::cPlayer2);
    }
    else if (settings::bPlayer2teamR)
    {
        if (!myTeamR) myTeamR = new TDMTeam(settings::clr2Team);
        players::addPlayer(myTeamR, controllers::cPlayer2);
    }

    if (!myTeamR && !myTeamL)
    {
        Color3f rand = Color3f::random();
        myTeamL = new TDMTeam(rand.inverted());
        myTeamR = new TDMTeam(rand);

    }
    else if (!myTeamL)
        myTeamL = new TDMTeam(myTeamR->color().inverted());
    else if (!myTeamR)
        myTeamR = new TDMTeam(myTeamL->color().inverted());

    teams::addTeam(myTeamL);
    teams::addTeam(myTeamR);

    for (int i=0; i < settings::iBotsLeft;  ++i)  players::addPlayer(myTeamL, controllers::cBot);
    for (int i=0; i < settings::iBotsRight; ++i)  players::addPlayer(myTeamR, controllers::cBot);

    init();
}

void TeamDeathMatch::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    Game::draw();
}

void TeamDeathMatch::restart()
{
    Game::restart();
    init();
}


void TeamDeathMatch::init()
{
    // Home* homeL = spaceObjects::addHome(HOME_LEFT, 100, myTeamL->color());
    // Home* homeR = spaceObjects::addHome(HOME_RIGHT, 100, myTeamR->color());
    Home* homeL = spaceObjects::addHome(HOME_LEFT, 100, teams::getTeamL()->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, 100, teams::getTeamR()->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();

    spaceObjects::populateSpace(5.f, 10.f, 4);
    ships::createTurrets();
    spaceObjects::addAsteroids();

    zones::createRaster(4,3);
}
