#pragma once

#include "DecoObjects/DecoObject.hpp"

class SpaceObject;


/// An object for drawing bolts between ships.

class Bolt : public DecoObject
{
    public:
        Bolt(SpaceObject *from, SpaceObject *to, float intensity)
            :from_(from)
            ,to_(to)
            ,intensity_(intensity >= 100.f ? 3 : (intensity >= 50.f ? 2 : 1))
            ,maxLifeTime_(0.3f)
            ,lifeTime_(0.f)
            ,boltImage_(0)
            ,flickerTimer_(0.f)
        {   }

        void draw() const override;

    private:
        SpaceObject *from_, *to_;
        int intensity_;
        mutable float maxLifeTime_, lifeTime_;
        mutable int boltImage_;
        mutable float flickerTimer_;
};
