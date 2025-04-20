#pragma once

#include "TrailEffects/Trail.hpp"
#include "System/Vector2f.hpp"
#include "System/Color3f.hpp"

#include <vector>

class SpaceObject;


class PersistantTrail : public Trail
{
    public:
        PersistantTrail(SpaceObject* target,
            float timeStep, float duration, float width,
            Color3f const& color);

        void update() override;;
        void draw() const override;
        
        bool isDead() const override;

    private:
        std::vector<Vector2f> points_;
        float alpha_;

        float timer_;
        const float duration_;
        const float timeStep_;

        const float width_;
        Color3f color_;
};
