/* Game.cpp

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

# include "Games/Game.hpp"

# include "SpaceObjects/spaceObjects.hpp"
# include "SpaceObjects/balls.hpp"
# include "SpaceObjects/ships.hpp"
# include "Particles/particles.hpp"
# include "System/timer.hpp"
# include "System/settings.hpp"
# include "Media/music.hpp"
# include "Players/players.hpp"
# include "Teams/Team.hpp"
# include "Hud/hud.hpp"
# include "Zones/zones.hpp"
# include "DecoObjects/decoObjects.hpp"
# include "Items/items.hpp"
# include "Menu/menus.hpp"
# include "System/window.hpp"
# include "Media/announcer.hpp"
# include "Media/music.hpp"
# include "Shaders/postFX.hpp"
# include "SpaceObjects/stars.hpp"
# include "TrailEffects/trailEffects.hpp"
# include "Teams/teams.hpp"

Game::Game(games::GameType const& type):
    type_(type),
    startTime_(timer::totalTime()) {
        switch (type_) {
            case games::gSpaceBall: case games::gCannonKeep: pointLimit_ = settings::C_pointLimit;    break;
            case games::gDeathMatch:                         pointLimit_ = settings::C_pointLimitDM;  break;
            case games::gMenu:                               pointLimit_ = 9999999;                   break;
            default:                                         pointLimit_ = settings::C_pointLimitTDM;
        }

    hud::init();
    stars::init();
    }

Game::~Game() {
    items::clear();
    ships::clear();
    balls::clear();
    physics::clear();
    particles::clear();
    spaceObjects::clear();
    controllers::clear();
    teams::clear();
    players::clear();
    zones::clear();
    decoObjects::clear();
    trailEffects::clear();
}

void Game::update() {
    music::update();
    announcer::update();
    hud::update();
    if ((!menus::visible()) || (type_ == games::gMenu)) {
        if (teams::getFirstPoints() < pointLimit_) {
            teams::update();
            controllers::update();
            if ((elapsedTime() > 4.f) || (type_ == games::gTutorial))
                ships::update();
            balls::update();
            spaceObjects::update();
        }
        else if(window::getInput().IsMouseButtonDown(sf::Mouse::Left) || window::getInput().IsMouseButtonDown(sf::Mouse::Right)
                || window::getInput().IsKeyDown(sf::Key::Space) || window::getInput().IsKeyDown(sf::Key::Return)) {
            games::restart();
            hud::displayStats(false);
        }
        else
            hud::displayStats();
        particles::update();
        zones::update();
        decoObjects::update();
        items::update();
        postFX::update();
        trailEffects::update();
    }
    else
        startTime_ += timer::frameTime();
}

void Game::draw() const {
    particles::drawLower();
    trailEffects::draw();
    controllers::draw();
    ships::draw();
    balls::draw();
    spaceObjects::draw();
    particles::drawHigher();
    decoObjects::draw();
    items::draw();
}

void Game::restart() {
    items::clear();
    ships::clear();
    balls::clear();
    physics::clear();
    particles::clear();
    spaceObjects::clear();
    zones::clear();
    decoObjects::clear();
    trailEffects::clear();
    if (teams::getFirstPoints() >= pointLimit_) {
        teams::resetTeamPoints();
        players::resetPlayerPoints();
    }
    if (games::type() == games::gCannonKeep || games::type() == games::gSpaceBall)
        players::resetPlayerPoints();
    startTime_ = timer::totalTime();
    controllers::resetBots();
    stars::init();
}

games::GameType Game::type() const {
    return type_;
}

float Game::elapsedTime() const {
    return timer::totalTime() - startTime_;
}




