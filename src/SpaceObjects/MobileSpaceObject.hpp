#pragma once

#include "SpaceObjects/SpaceObject.hpp"


class MobileSpaceObject: public SpaceObject
{
    public:
        MobileSpaceObject(spaceObjects::ObjectType type, Vector2f location, float radius, float mass)
            :SpaceObject(type, location, radius, mass)
        {   }

        Vector2f& velocity()
        {  return velocity_;  }

        //  cyclic borders
        void borders();

        bool cloud_ = false;  // no collision, can overlap,  cloud, plasma etc
        float chill_ = 0.f;

    protected:
        Vector2f velocity_;
        float acceleration_ = 0.f;
};
