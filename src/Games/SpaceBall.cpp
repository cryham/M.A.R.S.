#include "Games/SpaceBall.hpp"

#include "System/Vector2f.hpp"
#include "Teams/SBTeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "Players/players.hpp"
#include "Teams/teams.hpp"
#include "System/randomizer.hpp"


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
        myTeamL = new SBTeam(
            !settings::bPlayer1teamL && !settings::bPlayer2teamL ? settings::clr2Team
            : myTeamR->color().inverted());
    else if (!myTeamR)
        myTeamR = new SBTeam(
            !settings::bPlayer1teamR && !settings::bPlayer2teamR ? settings::clr1Team
            : myTeamL->color().inverted());

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

    if (settings::iBallsSB > 0)
        for (int i=0; i < settings::iBallsSB; ++i)
        {
            float r = randomizer::random(settings::iBallRadiusMin, settings::iBallRadiusMax);
            Vector2f pos = spaceObjects::possiblePlanetLocation(r, r * 1.2f);
            balls::addBall(r, pos);
        }
    else
        balls::addBall(settings::iBallRadiusMin);

    spaceObjects::populateSpace(5.f, 10.f, 4);
    ships::createTurrets();

    zones::detectTacticalZones();
    zones::createRaster(4, 3);
}
