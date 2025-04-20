#include "Games/DeathMatch.hpp"

#include "SpaceObjects/ships.hpp"
#include "Teams/DMTeam.hpp"
#include "Players/players.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Players/players.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "Teams/teams.hpp"
#include "System/randomizer.hpp"


DeathMatch::DeathMatch()
    :Game(games::gDeathMatch)
{
    weaponsFromUser();
    
    music::play();

    if (settings::bPlayer1teamL || settings::bPlayer1teamR)
        players::addPlayer (teams::addTeam(new DMTeam(settings::clr1Team)), controllers::cPlayer1);
    if (settings::bPlayer2teamL || settings::bPlayer2teamR)
        players::addPlayer (teams::addTeam(new DMTeam(settings::clr2Team)), controllers::cPlayer2);

    for (int i=0; i < settings::iBotsDeath; ++i)
    {
        Team* newTeam = teams::addTeam(new DMTeam());
        Color3f color(newTeam->color());
        color.h(newTeam->color().h()+10*randomizer::random(-5, 5));
        color.v(newTeam->color().v()+randomizer::random(-0.5f, 0.5f));
        players::addPlayer(newTeam, controllers::cBot, color);
    }
    init();
}

void DeathMatch::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    Game::draw();
}

void DeathMatch::restart()
{
    Game::restart();
    init();
}


void DeathMatch::init()
{
    teams::assignHomes(spaceObjects::addHome(HOME_MIDDLE, 100, Color3f::random()));
        // Color3f(randomizer::random(0.f, 0.1f), randomizer::random(0.f, 0.1f), randomizer::random(0.f, 0.1f))));
    players::createShips();

    spaceObjects::populateSpace(5.f, 10.f, 4);
    ships::createTurrets();
    spaceObjects::addAsteroids();

    zones::createRaster(4,3);
}
