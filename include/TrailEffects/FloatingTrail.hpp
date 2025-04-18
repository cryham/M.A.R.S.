#pragma once

#include "TrailEffects/Trail.hpp"
#include "System/Vector2f.hpp"
#include "System/Color3f.hpp"

#include <vector>

class SpaceObject;


class FloatingTrail: public Trail
{
    public:
        FloatingTrail(SpaceObject* target,
            float timeStep, float duration, float width,
            Color3f const& color);

        void update() override;;
        void draw() const override;
        
        bool isDead() const override;

    private:
        std::vector<Vector2f> points_;
        int frontIndex_;
        int length_;

        float timer_;
        float timeStep_;

        float width_;
        Color3f color_;
};
