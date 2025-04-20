#pragma once

#include "System/Vector2f.hpp"

class Player;


//  rotating mount for weapon, base for Ship and Turret

class Mount
{
    public:
        Mount(float rotation = 0.f, Player* owner = nullptr);

        Player* getOwner() const;

        float   rotation() const;
        virtual float    getRadius() = 0;

        virtual Vector2f getLocation() = 0;
        virtual Vector2f& getVelocity() = 0;

    protected:

        Player* owner_;

        // float radius_;

        float rotation_;
        float rotateSpeed_;
        // int left_, right_;  // inputs
};
