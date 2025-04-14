/* spaceObjects.cpp

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

#include "SpaceObjects/spaceObjects.hpp"

#include "SpaceObjects/Planet.hpp"
#include "SpaceObjects/Sun.hpp"
#include "SpaceObjects/BlackHole.hpp"
#include "SpaceObjects/Home.hpp"
#include "SpaceObjects/Turret.hpp"
#include "SpaceObjects/balls.hpp"
#include "Items/CannonControl.hpp"
#include "Items/items.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "System/settings.hpp"
#include "defines.hpp"
#include "System/randomizer.hpp"

#include <vector>
using namespace std;


namespace spaceObjects
{
    namespace
    {
        // objectList contains all homes as well, but for easy accessing
        // they are saved twice
        vector<SpaceObject*> objectList_;
        vector<Home*>        homeList_;
    }

    Vector2f possiblePlanetLocation(int radius, float minDistance)
    {
        int tries(0);
        bool newPlanetFits(false);

        while (!newPlanetFits && ++tries < 500)
        {
            // 100 is min distance between edge and planet
            int randx = rand() % (settings::iMapXsize - 2*(100 + radius)) + 100 + radius;
            int randy = rand() % (settings::iMapYsize - 2*(100 + radius)) + 100 + radius;
            Vector2f position(randx, randy);

            // check for collisions with other objects
            newPlanetFits = true;
            for (const auto& it : objectList_)
                if ((it->location() - position).lengthSquare() < pow(it->radius() + radius + settings::iMapMinPlanetGap, 2))
                    newPlanetFits = false;
            
            // check for collisions with balls
            Ball* ball = balls::getBall();
            if (ball)
            {
                if ((ball->location() - position).lengthSquare() < pow(ball->radius() + radius + 50, 2))
                    newPlanetFits = false;
            }
            // check for collisions with cannoncontrol
            CannonControl* control = items::getCannonControl();
            if (control)
            {
                if ((control->location() - position).lengthSquare() < pow(radius + 70.f, 2))
                    newPlanetFits = false;
            }

            if (newPlanetFits)
                return position;
        }
        return Vector2f(0,0);
    }

    void update()
    {
        for (auto& it : objectList_)
            it->update();
    }

    void draw()
    {
        for (const auto& it : objectList_)
            it->draw();
    }

    int randomPlanetSize()
    {
        // return randomizer::random(settings::iMapMinPlanetsSize, settings::iMapMaxPlanetsSize);
        return rand() % (settings::iMapMaxPlanetsSize - settings::iMapMinPlanetsSize) + settings::iMapMinPlanetsSize;
    }

    void addPlanet()
    {
        int radius = randomPlanetSize();
        Vector2f position = possiblePlanetLocation(radius, 100);
        if (position != Vector2f(0,0))
            addPlanet(position, radius);
    }

    void addPlanet(Vector2f const& location, float radius)
    {
        objectList_.push_back(new Planet(location, radius));
    }

    void addSun()
    {
        int radius = randomPlanetSize();
        Vector2f position = possiblePlanetLocation(radius, 200);
        if (position != Vector2f(0,0))
        {
            Sun* newSun = new Sun(position, radius);
            objectList_.push_back(newSun);
            decoObjects::addSunHeat(newSun);
        }
    }

    void addBlackHole()
    {
        int radius = randomPlanetSize();
        Vector2f position = possiblePlanetLocation(radius, 200);
        if (position != Vector2f(0,0))
            objectList_.push_back(new BlackHole(position, radius));
    }

    //  Home planets
    Home* addHome(int where, int life, Color3f const& color)
    {
        Vector2f position;
        float radius = settings::iMapHomeRadius;
        float mass = radius * 150.f;

        switch (where)
        {
            case HOME_LEFT:  position = Vector2f(-50,  (rand() % (settings::iMapYsize - 300)) + 150);  break;
            case HOME_RIGHT: position = Vector2f(settings::iMapXsize+50, (rand() % (settings::iMapYsize - 300)) + 150);  break;
            case HOME_RALLY: position = Vector2f(-150, (rand() % (settings::iMapYsize - 300)) + 150);
                             radius = 180.f;  mass *= 0.8f;  break;
            default:         position = possiblePlanetLocation(settings::iMapHomeRadius, 100);
        }
        return addHome(position, life, color, radius, mass);
    }

    Home* addHome(Vector2f const& location, int life, Color3f const& color, float radius, float mass)
    {
        Home* home = new Home(location, life, radius, mass, color);
        objectList_.push_back(home);
        homeList_.push_back(home);
        return home;
    }

    vector<Home*>const& getHomes()
    {
        return homeList_;
    }

    vector<SpaceObject*> const& getObjects()
    {
        return objectList_;
    }

    
    SpaceObject const* getObstacle(Vector2f const& start, Vector2f const& end, bool avoidBall, float minDistance)
    {
        SpaceObject const* closest(NULL);
        float closestDistance = FLT_MAX;

        for (auto it = objectList_.cbegin(); it != objectList_.cend(); ++it)
        {
            if ((*it)->type()!=oBlackHole)
            {
                float checkRadius = (*it)->radius();
                // increase radius, when start and end aren't close to object
                if ((start - (*it)->location()).lengthSquare() > pow((*it)->radius() + minDistance, 2) &&
                    (end   - (*it)->location()).lengthSquare() > pow((*it)->radius() + minDistance, 2))
                    checkRadius += minDistance;

                if (((end-start) * ((*it)->location() - start) > 0 &&
                    (pow(((end-start) * ((*it)->location() - start)) / (end-start).lengthSquare(), 2) -
                        (((*it)->location() - start).lengthSquare() -
                        pow(checkRadius, 2)) / (end-start).lengthSquare()) > 0))
                {
                    // check if object is in between or endpoint inside of obstacle
                    if ((end - start)*(end - (*it)->location()) >= 0.f ||
                        (end - (*it)->location()).lengthSquare() < pow((*it)->radius(), 2))
                    {
                        // hacky, should check for distance to impact location, but does not..
                        float distance = (start - (*it)->location()).lengthSquare();
                        if (distance < closestDistance)
                        {   closestDistance = distance;
                            closest = *it;
                        }
                    }
                }
            }
        }

        Ball* ball = balls::getBall();
        if (avoidBall && ball)
        {
            float checkRadius = ball->radius();
            // increase radius, when start and end aren't close to object
            if ((start - ball->location()).lengthSquare() > pow(ball->radius() + minDistance, 2) &&
                (end   - ball->location()).lengthSquare() > pow(ball->radius() + minDistance, 2))
                checkRadius += minDistance;

            if (((end-start)*(ball->location() - start) > 0 &&
                (pow(((end-start)*(ball->location() - start))/(end-start).lengthSquare(), 2) -
                ((ball->location() -start).lengthSquare() - pow(checkRadius, 2)) / (end-start).lengthSquare()) > 0))
            {
                // check if object is in between
                if ((end - start)*(end - ball->location()) >= 0.f)
                {
                    // hacky, should check for distance to impact location, but does not..
                    float distance = (start - ball->location()).lengthSquare();
                    if (distance < closestDistance)
                    {   closestDistance = distance;
                        closest = ball;
                    }
                }
            }
        }
        return closest;
    }

    bool isOnLine(Vector2f const& source, Vector2f const& direction, Vector2f const& target, float maxAngle)
    {
        return acos(direction.normalize() * (target - source).normalize()) < maxAngle *M_PI/360;
    }

    void clear()
    {
        for (auto& it : objectList_)
            delete it;
        objectList_.clear();
        homeList_.clear();
    }


    void populateSpace(float holePercentage, float sunPercentage, int maxObjects)
    {
        int count = randomizer::random(settings::iMapMinPlanets, settings::iMapMaxPlanets);
        int holes = holePercentage;
        int suns = sunPercentage;

        while (--count >= 0)
        {
            float percentage = randomizer::random(0.f, 100.f);

            if (percentage < holes)
                addBlackHole();
            else if (percentage < holes + suns)
                addSun();
            else
                addPlanet();
        }
    }
}
