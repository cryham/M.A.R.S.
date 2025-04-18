#include "TrailEffects/trailEffects.hpp"

#include "TrailEffects/FloatingTrail.hpp"
#include "TrailEffects/PersistantTrail.hpp"

#include <vector>
#include <set>


namespace trailEffects
{
    namespace
    {
        std::vector<Trail*> trails_;
        std::set<SpaceObject*> toBeDetached_;
    }

    void update()
    {
        auto it = trails_.begin();
        while (it != trails_.end())
        {
            if ((*it)->isDead())
            {
                delete *it;
                it = trails_.erase(it);
            }else
            {
                if (toBeDetached_.find((*it)->target()) != toBeDetached_.end())
                    (*it)->detach();
                (*it)->update();
                ++it;
            }
        }
        toBeDetached_.clear();
    }

    void draw()
    {
        for (const auto& it : trails_)
            it->draw();
    }

    Trail* attach(SpaceObject* target, float timeStep, float duration, float width, Color3f const& color, bool persistant)
    {
        Trail* trail;
        if (persistant)
            trail = new PersistantTrail(target, timeStep, duration, width, color);
        else
            trail = new FloatingTrail(target, timeStep, duration, width, color);

        trails_.push_back(trail);
        return trail;
    }

    void detach(SpaceObject* target)
    {
        toBeDetached_.insert(target);
    }

    int  count()
    {
        return trails_.size();
    }

    void clear()
    {
        for (auto& it : trails_)
            delete it;
        trails_.clear();
    }
}
