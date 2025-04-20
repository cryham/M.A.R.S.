#include "Games/Game.hpp"

#include "SpaceObjects/asteroids.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "SpaceObjects/balls.hpp"
#include "SpaceObjects/ships.hpp"
#include "Particles/particles.hpp"
#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Players/players.hpp"
#include "Teams/Team.hpp"
#include "Hud/hud.hpp"
#include "Weapons/weapons.hpp"
#include "Zones/zones.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "Items/items.hpp"
#include "Menu/menus.hpp"
#include "Media/announcer.hpp"
#include "SpaceObjects/stars.hpp"
#include "TrailEffects/trailEffects.hpp"
#include "SpaceObjects/physics.hpp"
#include "Teams/teams.hpp"


Game::Game(games::GameType const& type):
    type_(type),
    startTime_(timer::totalTime()),
    ended_(false)
{
    switch (type_)
    {
        case games::gSpaceBall:  pointLimit_ = settings::iPointLimitSB;   break;
        case games::gCannonKeep: pointLimit_ = settings::iPointLimitCK;   break;
        case games::gDeathMatch: pointLimit_ = settings::iPointLimitDM;   break;
        case games::gMenu:       pointLimit_ = 9999999;                   break;
        default:                 pointLimit_ = settings::iPointLimitTDM;
    }
    hud::init();
    stars::init();
}

Game::~Game()
{
    items::clear();
    ships::clear();

    balls::clear();
    asteroids::clear();

    physics::clear();
    particles::clear();
    spaceObjects::clear();
    
    controllers::clear();
    teams::clear();
    players::clear();
    zones::clear();
    
    decoObjects::clear();
    trailEffects::clear();
    timer::resetSlowMotion();
}


//  update
void Game::update()
{
    announcer::update();
    hud::update();

    if (!menus::visible() || type_ == games::gMenu)
    {
        spaceObjects::update();
        particles::update();
        items::update();
        // postFX::update();
        trailEffects::update();

        if (teams::getFirstPoints() >= pointLimit_)
        {
            if (!ended_)
            {
                Team* best = nullptr;
                int   most(0);
                for (auto& it : teams::getAllTeams())
                    if (most < it->points())
                    {
                        best = it;
                        most = it->points();
                    }
                if (best)
                    best->addVictory();
                ended_ = true;
            }
            hud::displayStats();

            if (type_ != games::gDeathMatch)
                hud::displayPoints();
        }else
        {
            decoObjects::update();

            ships::update();  // and turrets
            balls::update();
            asteroids::update();

            teams::update();
            controllers::update();
            zones::update();
        }
    }
    else
        startTime_ += timer::frameTime();
}

//  draw
void Game::draw() const
{
    if (settings::iStarField)
        particles::drawStars();
    
    particles::drawLower();
    trailEffects::draw();
    
    controllers::draw();
    ships::draw();

    asteroids::draw();
    balls::draw();
    
    spaceObjects::draw();
    ships::drawTurrets();

    particles::drawHigher();
    decoObjects::draw();
    items::draw();
}

void Game::restart()
{
    items::clear();
    ships::clear();

    balls::clear();
    asteroids::clear();

    physics::clear();
    particles::clear();

    spaceObjects::clear();
    zones::clear();

    decoObjects::clear();
    trailEffects::clear();

    teams::resetTeamPoints();
    players::resetPlayerPoints();
    startTime_ = timer::totalTime();
    controllers::resetBots();
    
    stars::init();
    hud::displayStats(false);
    hud::displayPoints(false);
    timer::resetSlowMotion();
    ended_ = false;
}


void Game::weaponsClear()
{
    for (int i=0; i < weapons::All; ++i)
        settings::bEnabledWeapons[i] = false;
    for (int i=0; i < specials::All; ++i)
        settings::bEnabledSpecials[i] = false;
}

void Game::weaponsFromUser()
{
    for (int i=0; i < weapons::All; ++i)
        settings::bEnabledWeapons[i] = settings::bEnabledWeaponsByUser[i];
    
    settings::bEnabledWeapons[weapons::wInsta] = false;
    for (int i=0; i < specials::All; ++i)
        settings::bEnabledSpecials[i] = settings::bEnabledSpecialsByUser[i];
}


games::GameType Game::type() const
{
    return type_;
}

float Game::elapsedTime() const
{
    return timer::totalTime() - startTime_;
}

bool Game::ended() const
{
    return ended_;
}
