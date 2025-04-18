#include "DecoObjects/decoObjects.hpp"

#include "DecoObjects/Cannon.hpp"
#include "DecoObjects/PlanetSign.hpp"
#include "DecoObjects/SunHeat.hpp"
#include "DecoObjects/ShipName.hpp"
#include "DecoObjects/ShipHighlight.hpp"
#include "DecoObjects/Evil.hpp"
#include "DecoObjects/Ice.hpp"
#include "DecoObjects/Bolt.hpp"

#include <SFML/System.hpp>
#include <vector>
#include <list>


namespace decoObjects
{
    namespace
    {
        Cannon* cannon_ = nullptr;
        std::vector<DecoObject*> decos_;
        std::vector<DecoObject*> heats_;
        std::vector<DecoObject*> names_;
        std::list<DecoObject*> ices_ ;
        std::list<DecoObject*> bolts_ ;
    }

    void update()
    {
        if (cannon_)
            cannon_->update();
    }

    void draw()
    {
        if (cannon_)
            cannon_->draw();
        
        for (const auto& it : decos_)
            it->draw();

        for (auto it = ices_.begin(); it != ices_.end(); ++it)
        {
            if (*it)
                (*it)->draw();
            else
                it = ices_.erase(it);
        }

        for (auto it = bolts_.begin(); it != bolts_.end(); ++it)
        {
            if (*it)
                (*it)->draw();
            else
                it = bolts_.erase(it);
        }
    }

    void drawHeat()
    {
        for (const auto& it : heats_)
            it->draw();
    }

    void drawNames()
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        for (const auto& it : names_)
            it->draw();
    }

    void drawArrow(Vector2f const& from,  Vector2f const& to, Color3f const& color, float width)
    {
        Vector2f direction((to-from).normalize()*width*0.5f);
        Vector2f normal(direction.y_, -direction.x_);

        glBlendFunc(GL_ONE, GL_ONE);
        glLineWidth(width);

        glBegin(GL_TRIANGLES);
            (color*0.5f).gl3f();
            glVertex2f(from.x_,from.y_);

            color.gl3f();
            glVertex2f(to.x_-normal.x_,to.y_-normal.y_);
            glVertex2f(to.x_+normal.x_,to.y_+normal.y_);

            glVertex2f(to.x_+direction.x_*3.f,to.y_+direction.y_*3.f);
            glVertex2f(to.x_+normal.x_*2.f,to.y_+normal.y_*2.f);
            glVertex2f(to.x_-normal.x_*2.f,to.y_-normal.y_*2.f);
        glEnd();
    }

    void addCannon()
    {
        cannon_ = new Cannon();
        decos_.push_back(new Evil());
    }

    void addPlanetSign(Planet* planet)
    {
        decos_.push_back(new PlanetSign(planet));
    }

    void addSunHeat(Sun* sun)
    {
        heats_.push_back(new SunHeat(sun));
    }

    void addIce(Ship* ship)
    {
        ices_.push_back(new Ice<Ship>(ship));
    }

    void addIce(Ball* ball)
    {
        ices_.push_back(new Ice<Ball>(ball));
    }

    void addIce(AmmoRocket* rocket)
    {
        ices_.push_back(new Ice<AmmoRocket>(rocket));
    }

    void removeIce(DecoObject const* toBeRemoved)
    {
        for (auto it = ices_.begin(); it != ices_.end(); ++it)
            if (*it == toBeRemoved)
            {
                delete *it;
                *it = nullptr;
                break;
            }
    }

    void addBolt(SpaceObject* from, SpaceObject* to, float intensity)
    {
        bolts_.push_back(new Bolt(from, to, intensity));
    }

    void removeBolt(DecoObject const* toBeRemoved)
    {
        for (auto it = bolts_.begin(); it != bolts_.end(); ++it)
            if (*it == toBeRemoved)
            {
                delete *it;
                *it = nullptr;
                break;
            }
    }

    void addName(Ship* ship, bool bar)
    {
        names_.push_back(new ShipName(ship, bar));
    }

    void addHighlight(Ship* ship)
    {
        decos_.push_back(new ShipHighlight(ship));
    }

    void clear()
    {
        if (cannon_)
        {   delete cannon_;
            cannon_ = nullptr;
        }
        for (auto& it : decos_)
            delete it;
        for (auto& it : heats_)
            delete it;
        for (auto& it : names_)
            delete it;
        
        decos_.clear();
        heats_.clear();
        names_.clear();
        ices_.clear();
    }
}
