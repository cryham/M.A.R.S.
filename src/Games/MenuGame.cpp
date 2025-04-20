#include "Games/MenuGame.hpp"

#include "Teams/GITeam.hpp"
#include "System/settings.hpp"
#include "Media/music.hpp"
#include "Hud/hud.hpp"
#include "Menu/menus.hpp"
#include "Menu/ChooseLanguage.hpp"
#include "Players/players.hpp"
#include "SpaceObjects/Home.hpp"
#include "Teams/teams.hpp"


MenuGame::MenuGame()
    :Game(games::gMenu)
{
    weaponsClear();
    settings::bEnabledWeapons[weapons::wInsta] = true;

    music::play(settings::sDataPath + "audio/menu.ogg");

    Color3f rand = Color3f::random();

    Team* myTeamL = teams::addTeam(new GITeam(rand));
    Team* myTeamR = teams::addTeam(new GITeam(rand.inverted()));

    for (int i=0; i < 4; ++i)  players::addPlayer(myTeamL, controllers::cBot);
    for (int i=0; i < 4; ++i)  players::addPlayer(myTeamR, controllers::cBot);

    Home* homeL = spaceObjects::addHome(HOME_LEFT, 100, myTeamL->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, 100, myTeamR->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();

    menus::showMain();

    if (settings::bShowSelectLanguage)
    {
        menus::showWindow(ChooseLanguage::get());
        settings::bShowSelectLanguage = false;
    }

    spaceObjects::populateSpace(40.f, 5.f, 2);
    spaceObjects::addAsteroids();  //-
    
    zones::createRaster(4,3);
}

void MenuGame::restart()
{
    Game::restart();

    Home* homeL = spaceObjects::addHome(HOME_LEFT, 100, teams::getTeamL()->color());
    Home* homeR = spaceObjects::addHome(HOME_RIGHT, 100, teams::getTeamR()->color());

    teams::assignHomes(homeL, homeR);
    players::createShips();

    menus::showMain();

    spaceObjects::populateSpace(40.f, 5.f, 2);
    spaceObjects::addAsteroids();

    zones::createRaster(4,3);
}
