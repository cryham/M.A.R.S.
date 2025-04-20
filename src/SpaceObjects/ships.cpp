#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/Turret.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "SpaceObjects/Home.hpp"
#include "SpaceObjects/Planet.hpp"
#include "System/Vector2f.hpp"
#include "System/randomizer.hpp"
#include "System/settings.hpp"

#include <vector>


namespace ships  // and turrets
{
    namespace
    {
        std::vector<Ship*> shipList_;
        std::vector<Turret*> turretList_;
    }

    void addShip(Vector2f const& location, float rotation, Player* owner)
    {
        shipList_.push_back(new Ship(location, rotation, owner));
    }

    void addTurret(Vector2f const& location, float rotation, Player* owner)
    {
        turretList_.push_back(new Turret(location, rotation, owner));
    }

    void update()
    {
        for (auto& it : shipList_)
            it->update();
        for (auto& it : turretList_)
            it->update();
    }

    //  draw  ----
    void draw()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));

        for (const auto& it : shipList_)
            it->drawWeapon();

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

        for (const auto& it : shipList_)
            it->draw();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawTurrets()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));

        for (const auto& it : turretList_)
            it->drawWeapon();

        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

        for (const auto& it : turretList_)
            it->draw();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    std::vector<Ship*> const& getShips()
    {
        return shipList_;
    }

    std::vector<Turret*> const& getTurrets()
    {
        return turretList_;
    }

    void clear()
    {
        for (auto& it : shipList_)
            delete it;
        shipList_.clear();
        
        for (auto& it : turretList_)
            delete it;
        turretList_.clear();
    }


    //  angle
    float GetAngle(float x, float y)
    {
        if (x == 0.f && y == 0.f)
            return 0.f;

        if (y == 0.f)
            return (x < 0.f) ? M_PI : 0.f;
        else
            return (y < 0.f) ? atan2f(-y, x) : (2.f * M_PI - atan2f(y, x));
    }


    //  add Turrets
    //----------------------------------------------------------------------------------------------------------------------------------
    void createTurrets()
    {
        float tr = settings::iShipRadius;
        Vector2f pos;  float ang;
        int tries = 0;
        bool out;

        //  get new random pos
        auto newPos = [&](Vector2f p, float r)
        {
            auto dir = Vector2f::randDir();
            ang = GetAngle(dir.x_, dir.y_);
            pos = p + dir * r;

            //  outside of map
            out = pos.x_ < tr || pos.y_ < tr ||
                pos.x_ > settings::iMapXsize - tr || pos.y_ > settings::iMapYsize - tr;
            
            // std::cout << "tur1  " << pos.x_ << " " << pos.y_ << "  out " << (out?"Y":"n") << std::endl;
            //  too close to other turrets
            if (!out && !turretList_.empty())
            {
                float dist = FLT_MAX;
                for (auto& turret : turretList_)
                {
                    float d = (pos - turret->location()).length();
                    if (d < dist)
                        dist = d;
                }
                out = dist < 100;
                // std::cout << "tur2- dist " << dist << "  out " << (out?"Y":"n") << std::endl;
            }
            ++tries;
        };

        //  random in space
        int count = settings::iTurretsInSpace;
            for (int i=0; i < count; ++i)
            {
                tries = 0;
                do
                {   Vector2f pos = spaceObjects::possiblePlanetLocation(50, 150);
                    newPos(pos, 0.f);
                }
                while (tries < 20 && out);
                addTurret(pos, ang, nullptr);
            }

        //  on Homes
        count = settings::iTurretsOnHome;
        for (auto& home : spaceObjects::getHomes())
            for (int i=0; i < count; ++i)
            {
                tries = 0;
                do
                {   float r = home->radius() * randomizer::random(1.2f, 1.3f);
                    newPos(home->location(), r);
                }
                while (tries < 20 && out);
                addTurret(pos, ang, nullptr);
            }
        
        //  on Planets
        count = settings::iTurretsOnPlanet;
        for (auto& planet : spaceObjects::getPlanets())
            for (int i=0; i < count; ++i)
            {
                tries = 0;
                do
                {   float r = planet->radius() * randomizer::random(1.2f, 1.3f);
                    newPos(planet->location(), r);
                }
                while (tries < 20 && out);
                addTurret(pos, ang, nullptr);
            }
    }
}
