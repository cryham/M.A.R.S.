#include "Games/CannonKeep.hpp"

#include "SpaceObjects/ships.hpp"
#include "Teams/CKTeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Items/items.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "Players/players.hpp"
#include "Teams/teams.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "Weapons/weapons.hpp"


CannonKeep::CannonKeep()
    :Game(games::gCannonKeep)
{
    weaponsFromUser();

    music::play();

    Team* myTeamL = nullptr;
    Team* myTeamR = nullptr;

    if (settings::bPlayer1teamL)
    {
        myTeamL = new CKTeam(settings::clr1Team);
        players::addPlayer(myTeamL, controllers::cPlayer1);
    }
    else if (settings::bPlayer1teamR)
    {
        myTeamR = new CKTeam(settings::clr1Team);
        players::addPlayer(myTeamR, controllers::cPlayer1);
    }

    if (settings::bPlayer2teamL)
    {
        if (!myTeamL)
            myTeamL = new CKTeam(settings::clr2Team);
        players::addPlayer(myTeamL, controllers::cPlayer2);
    }
    else if (settings::bPlayer2teamR)
    {
        if (!myTeamR)
            myTeamR = new CKTeam(settings::clr2Team);
        players::addPlayer(myTeamR, controllers::cPlayer2);
    }

    if (!myTeamR && !myTeamL)
    {
        Color3f rand = Color3f::random();
        myTeamL = new CKTeam(rand.inverted());
        myTeamR = new CKTeam(rand);

    }
    else if (!myTeamL)
        myTeamL = new CKTeam(myTeamR->color().inverted());
    else if (!myTeamR)
        myTeamR = new CKTeam(myTeamL->color().inverted());

    teams::addTeam(myTeamL);
    teams::addTeam(myTeamR);

    for (int i=0; i < settings::iBotsLeft;  ++i)  players::addPlayer(myTeamL, controllers::cBot);
    for (int i=0; i < settings::iBotsRight; ++i)  players::addPlayer(myTeamR, controllers::cBot);

    init();
}

void CannonKeep::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    Game::draw();
}

void CannonKeep::restart()
{
    Game::restart();
    init();
}


void CannonKeep::init()
{
    Home* homeL = spaceObjects::addHome(HOME_LEFT, settings::iPointLimitCK, teams::getTeamL()->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, settings::iPointLimitCK, teams::getTeamR()->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();
    decoObjects::addCannon();
    items::addCannonControl();

    spaceObjects::populateSpace(5.f, 10.f, 4);
    ships::createTurrets();
    spaceObjects::addAsteroids();

    zones::createRaster(4,3);
}
