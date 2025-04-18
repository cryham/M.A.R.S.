#include "Games/Rally.hpp"

#include "Teams/DMTeam.hpp"
#include "Players/players.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Players/players.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "SpaceObjects/Track.hpp"
#include "Teams/teams.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "TrailEffects/Trail.hpp"
#include "System/randomizer.hpp"


Rally::Rally()
    :Game(games::gRally)
    ,track_(0)
{
    copyFromUser();

    music::play();

    if (settings::bPlayer1teamL  | settings::bPlayer1teamR)
        players::addPlayer (teams::addTeam(new DMTeam(settings::clr1Team)), controllers::cPlayer1);
    if (settings::bPlayer2teamL | settings::bPlayer2teamR)
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

Rally::~Rally()
{
    delete track_;
}

void Rally::draw() const
{
    if (settings::bDrawZones)
        zones::draw();
    track_->draw();
    Game::draw();
}

void Rally::restart()
{
    Game::restart();
    init();
}


void Rally::init()
{
    Home* home = spaceObjects::addHome(HOME_RALLY, 100, Color3f(1.f, 1.f, 1.f));
    teams::assignHomes(home);
    players::createShips();

    //spaceObjects::populateSpace(5.f, 10.f, 4);
    zones::createRaster(4,3);

    delete track_;
    track_ = new Track(home);
}
