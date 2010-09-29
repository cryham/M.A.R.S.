/* BotControllerMovement.cpp

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

# include "Controllers/BotController.hpp"

# include "SpaceObjects/Ship.hpp"
# include "Games/games.hpp"
# include "System/settings.hpp"
# include "SpaceObjects/balls.hpp"
# include "Players/Player.hpp"
# include "Players/Team.hpp"
# include "System/window.hpp"
# include "Zones/TacticalZone.hpp"
# include "Zones/RasterZone.hpp"
int pathDepth = 0;

void BotController::charge() const {
    Vector2f direction = ship()->location() - slave_->team()->home()->location();
    turnTo(direction + ship()->location());
    slaveFire(false);
    slaveUp(false);
}

void BotController::land() const {
    moveTo(slave_->team()->home()->location(), 50.f, true, 0.f, true);
}

void BotController::kickBallToEnemy() const {
    Vector2f shipLocation = ship()->location();
    Vector2f ballLocation = balls::getBall()->location_;
    Vector2f ballVelocity = balls::getBall()->velocity_;
    Vector2f targetPlanetLocation = players::getEnemy(slave_->team())->home()->location();
    float    shipRotation = ship()->rotation_*M_PI/180.f;
    Vector2f shipDirection(std::cos(shipRotation), std::sin(shipRotation));
    shipDirection = shipDirection.normalize();
    targetPlanetLocation = calcPath(targetPlanetLocation, false);
    ballLocation = calcPath(ballLocation, false);

    // is ship, ball and target planet in row?
    if (spaceObjects::isOnLine(shipLocation, ballLocation-shipLocation, targetPlanetLocation, players::getEnemy(slave_->team())->home()->radius()*1.5f)) {
        // if so, is the ship correctly oriented
        if (shipDirection*(ballLocation - shipLocation) > 0.8f) {
            // kick ball
            moveTo(targetPlanetLocation, 0, false);

            if (ballLocation == balls::getBall()->location_ && !balls::getBall()->atStart())
                shootPoint(ballLocation);
        }
        else {
            // rotate ship correctly
            turnTo(ballLocation);
        }
    }
    else {
        // move behind the ball
        Vector2f aimPosition = ballLocation + (ballLocation - targetPlanetLocation).normalize()*70 + ballVelocity*0.5f;
        moveTo(aimPosition, 0.2f, true);
    }

    shootEnemy();
}

void BotController::kickBallOutHome() const {
    Vector2f shipLocation = ship()->location();
    Vector2f ballLocation = balls::getBall()->location();
    float    shipRotation = ship()->rotation_*M_PI/180;
    Vector2f shipDirection = Vector2f (std::cos(shipRotation), std::sin(shipRotation));
    Vector2f homeLocation = slave_->team()->home()->location();
    shipDirection = shipDirection.normalize();
    Vector2f ballShip = shipLocation - ballLocation;

    // is ship between ball and planet?
    if (spaceObjects::isOnLine(ballLocation, ballShip, homeLocation, slave_->team()->home()->radius())) {
        // wait a bit and face ball
        if (ballShip.lengthSquare() > 2500.f) {
            turnTo(ballLocation);
            shootPoint(ballLocation);
        }
        else {
            moveTo(shipLocation + ballShip*2.f, 0, false);
            shootPoint(ballLocation);
        }
    }
    else {
        // go to planet surface, facing the ball
        Vector2f direction = (ballLocation - homeLocation).normalize();
        direction = direction * (slave_->team()->home()->radius() + ship()->radius()+30.f);
        Vector2f location = slave_->team()->home()->location()+direction;
        moveTo(location, 0.2f, true);
    }
}

void BotController::waitForBall() const {
    Vector2f ballLocation = balls::getBall()->location_;
    Vector2f targetPlanetLocation = players::getEnemy(slave_->team())->home()->location();
    targetPlanetLocation = calcPath(targetPlanetLocation, false);
    ballLocation = calcPath(ballLocation, false);

    Vector2f planetBall = (ballLocation - targetPlanetLocation).normalize();
    Vector2f aimPosition = ballLocation + planetBall*50;
    moveTo(aimPosition, 1.5f, true);

    shootEnemy();
}


void BotController::attackTarget() {
    if (target_ != NULL) {
        moveTo(target_->location(), 0.f, true);
        shootEnemy(target_);
        if (target_->getLife() == 0.f) {
            aggroTable_[target_] = 0.f;
            float maxAggro(0.f);
            for (std::map<Ship*, float>::iterator it = aggroTable_.begin(); it != aggroTable_.end(); ++it) {
                if(it->second > maxAggro && it->first->getLife() > 0.f)
                    maxAggro = it->second;
            }

            if(maxAggro == 0.f) {
                float closest(FLT_MAX);
                for (std::map<Ship*, float>::iterator it = aggroTable_.begin(); it != aggroTable_.end(); ++it)
                    if(((it->first->location() - ship()->location()).lengthSquare() < closest) && (it->first->getLife() > 0.f)) {
                        closest = (it->first->location() - ship()->location()).lengthSquare();
                        target_ = it->first;
                    }
                if(closest == FLT_MAX)
                    target_ = NULL;
                else
                    aggroTable_[target_] = 100.f;
            }
            else
                for (std::map<Ship*, float>::iterator it = aggroTable_.begin(); it != aggroTable_.end(); ++it) {
                    if((it->second == maxAggro) && (it->first->getLife() > 0.f)) {
                        it->second = 100.f;
                        target_ = it->first;
                    }
                    else
                        it->second /= (maxAggro/100.f);
            }
        }
    }
}

void BotController::protectZone() {
    TacticalZone* tmp(toCover_);
    toCover_ = zones::toProtect(slave_->team());
    if (tmp != toCover_ || nextRoutePoint_.x_ == FLT_MAX) {
            nextRoutePoint_ = toCover_->getRandomPoint();
    }
    if (moveTo(nextRoutePoint_, 0.5f, false, toCover_->radius_ / 4.f)) {
        nextRoutePoint_.x_ = FLT_MAX;
    }
}

void BotController::switchToWeapon() {
    slaveFire();
    slaveLeft();
    if(ship()->currentWeapon_->getName() == "FLUBBA")
        slaveLeft();
    slaveFire();
    actions_[BOT_CHANGE_WEAPON] = 0;
}

void BotController::escape() {
    if (nextRoutePoint_.x_ == FLT_MAX)
        nextRoutePoint_ = zones::freeZone()->getRandomPoint();
    if (moveTo(nextRoutePoint_, 0.4f, false, 100.f))
        nextRoutePoint_.x_ = FLT_MAX;
}

void  BotController::startFight() {
    if (nextRoutePoint_.x_ == FLT_MAX)
        nextRoutePoint_ = zones::freeZone()->getRandomPoint();
    if (moveTo(nextRoutePoint_, 0.9f, false, 250.f)) {
        std::vector<Team*> const& enemies = players::getAllTeams();
        if(!enemies.empty()) {
            float distance(FLT_MAX);
            for (std::vector<Team*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it)
                if((*it) != slave_->team()) {
                    std::vector<Player*> const& enemyMembers = (*it)->members();
                    for (std::vector<Player*>::const_iterator it = enemyMembers.begin(); it != enemyMembers.end(); ++it) {
                        if(((*it)->ship()->location() - ship()->location_).lengthSquare() < distance) {
                            distance = ((*it)->ship()->location()-ship()->location_).lengthSquare();
                            target_ = (*it)->ship();
                        }
                    }
                }
            if (target_)
                aggroTable_[target_] = 100.f;
        }
     }
}

bool BotController::moveTo(Vector2f const& location, float stopFactor, bool avoidBall, float minDistance, bool goingToLand) const {
    Vector2f targetPoint = calcPath(location, avoidBall);

    Vector2f shipLocation = ship()->location_;
    Vector2f shipVelocity = ship()->velocity_;
    float    shipRotation = ship()->rotation_*M_PI/180.f;
    Vector2f shipDirection = Vector2f(std::cos(shipRotation), std::sin(shipRotation));

    Vector2f aimDirection;
    if (targetPoint == location) aimDirection = targetPoint - shipLocation - shipVelocity*stopFactor*shipVelocity.lengthSquare()*0.00003f;
    else                         aimDirection = targetPoint - shipLocation - shipVelocity*0.8f*shipVelocity.lengthSquare()*0.00003f;

    aimDirection = aimDirection.normalize();

    turnTo(aimDirection+shipLocation);

    Vector2f velocityInAimDirection = aimDirection*(shipVelocity*aimDirection);
    float distance = (targetPoint-shipLocation).lengthSquare();

    bool accelerate(false);
    if (velocityInAimDirection.lengthSquare() < 90000.f || shipVelocity*aimDirection < 0.f)
        if (distance > 2500 || (shipVelocity*aimDirection < 0.f && (distance > 250.f || !goingToLand)))
            if (spaceObjects::isOnLine(shipLocation, shipDirection, shipLocation+aimDirection*50.f, 10.f))
                accelerate = true;

    slaveUp(accelerate);

    // draw lines
    if (settings::C_drawAIPath) {

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glLineWidth(1);

        glBegin(GL_LINES);
        if (targetPoint == location) {
            glColor4f(0,1,0, 0.8f);
            glVertex2f(shipLocation.x_, shipLocation.y_);
            glVertex2f(targetPoint.x_, targetPoint.y_);
        }
        else {
            glColor4f(0,1,0, 0.8f);
            glVertex2f(shipLocation.x_, shipLocation.y_);
            glColor4f(1,0,0, 0.8f);
            glVertex2f(targetPoint.x_, targetPoint.y_);
            glVertex2f(targetPoint.x_, targetPoint.y_);
            glColor4f(0,1,0, 0.8f);
            glVertex2f(location.x_, location.y_);
        }
        glEnd();

        glPointSize(8);
        glBegin(GL_POINTS);
        glColor3f(0,1,0);
        Vector2f temp = aimDirection*50 + shipLocation;
            glVertex2f(temp.x_, temp.y_);
        glEnd();
    }

    return ((location - shipLocation).lengthSquare() < minDistance * minDistance);
}

void BotController::turnTo(Vector2f const& location) const {
    float    shipRotation = ship()->rotation_*M_PI/180.f;
    Vector2f aimDirection = location - ship()->location();
    if (aimDirection.y_*std::cos(shipRotation)-aimDirection.x_*std::sin(shipRotation) > 0) slaveRight(true);
    else                                                                                   slaveLeft (true);
}

Vector2f BotController::calcPath(Vector2f const& endPoint, bool avoidBall) const {
    // get some useful data...
    Vector2f toEndPoint  = (endPoint - ship()->location()).normalize();
    Vector2f targetPoint =  endPoint;

    if (++pathDepth < 5) {
        // check for collision with planet
        SpaceObject const* obstacle = spaceObjects::getObstacle(ship()->location(), endPoint, avoidBall, 40.f);

        if (obstacle != NULL) {
            // special case: obstacle center is target point
            if (obstacle->location() == endPoint) {
                pathDepth = 0;
                return obstacle->location() - toEndPoint*(obstacle->radius() + 20.f);
            }

            // calculate alternative point near obstacle
            Vector2f obstacleToStart(ship()->location() - obstacle->location());
            Vector2f normalToPath(-toEndPoint.y_, toEndPoint.x_);
            Vector2f newEndPoint;
            // if path hits obstacle exactly in the center
            if (obstacleToStart * normalToPath == 0.f)
                newEndPoint = obstacle->location() - normalToPath*(obstacle->radius() + 60.f);
            else {
                normalToPath = (normalToPath * (obstacleToStart * normalToPath)).normalize();
                newEndPoint = obstacle->location() + normalToPath*(obstacle->radius() + 60.f);
            }
            // check whether new endPoint is in an obstacle again... (happens, whenever two obstacles are close to each other)
            SpaceObject const* newObstacle = spaceObjects::getObstacle(ship()->location(), newEndPoint, avoidBall, 40.f);

            // if a new obstacle was found, calculate the midpoint of both
            if (newObstacle != NULL && obstacle != newObstacle) {
                Vector2f obst1obst2 = (newObstacle->location() - obstacle->location()).normalize();
                // get points on surface of obstacles
                Vector2f obst1 = obstacle->   location() + obst1obst2*obstacle->   radius();
                Vector2f obst2 = newObstacle->location() - obst1obst2*newObstacle->radius();
                // get midpoint between these
                newEndPoint = (obst1 + obst2) / 2;
            }
            // calculate path to newly found endpoint recursivly
            targetPoint = calcPath(newEndPoint, avoidBall);
        }
    }
    pathDepth = 0;
    return targetPoint;
}

void BotController::shootEnemy(Ship* enemyShip) const {
    float    shipRotation = ship()->rotation_*M_PI/180.f;
    Vector2f shipDirection = Vector2f(std::cos(shipRotation), std::sin(shipRotation)).normalize();
    if (enemyShip == NULL) {
        std::vector<Player*>const& enemies = players::getEnemy(slave_->team())->members();
        for (std::vector<Player*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it) {
            Vector2f pathToEnemy = calcPath((*it)->ship()->location(), false);
            if (pathToEnemy == (*it)->ship()->location() && spaceObjects::isOnLine(ship()->location(), shipDirection, pathToEnemy, 10.f)) {
                shootPoint(pathToEnemy);
                break;
            }
        }
    }
    else {
        Vector2f pathToEnemy = calcPath(enemyShip->location(), true);
            if (pathToEnemy == enemyShip->location() && spaceObjects::isOnLine(ship()->location(), shipDirection, pathToEnemy, 10.f))
                shootPoint(pathToEnemy);
    }
}

void BotController::shootPoint(Vector2f const& location) const {
    float minDistance(FLT_MAX);
    if (ship()->currentWeapon_->getName() == "SHOTGUN")
        minDistance = 90000.f;
    else if(ship()->currentWeapon_->getName() == "BURNER")
        minDistance = 40000.f;
    if((location - ship()->location()).lengthSquare() < minDistance) {
        bool doShoot(true);
        std::vector<Player*>const& teamMates = slave_->team()->members();
        for (std::vector<Player*>::const_iterator it = teamMates.begin(); it != teamMates.end(); ++it) {
            if (*it != slave_)
                if(spaceObjects::isOnLine(ship()->location(), location - ship()->location(), location, 20.f)
                   && ((location - ship()->location()).lengthSquare() > ((*it)->ship()->location() - ship()->location()).lengthSquare())) {
                    doShoot = false;
                    break;
                }
        }
        slaveFire(doShoot);
    }
}


