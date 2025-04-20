#pragma once

#include "SpaceObjects/MobileSpaceObject.hpp"
#include "Players/Player.hpp"
#include "System/Color3f.hpp"


class Asteroid : public MobileSpaceObject
{
    public:
        Asteroid(Vector2f const& location, float radius, int type);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        void onShockWave(Player* source, float intensity) override;

        bool atStart() const      {   return sticky_;  }
        bool isVisible() const    {   return visible_;  }
        float heatAmount() const  {   return heatTimer_ * 5.f;  }

        Player* lastShooter() const {   return lastShooter_;  }
        void resetShooter()         {   lastShooter_ = nullptr;  }

        friend class BotController;
        friend class Freezer;
        friend class Shocker;
        template <typename Object> friend class Ice;

    private:
        void explode();
        void respawn();

        float rotation_;
        float rotateSpeed_;

        float frozen_;
        bool  sticky_, visible_;

        Vector2f respawnLocation_;
        float respawnRotation_;

        float heatTimer_, smokeTimer_, respawnTimer_;

        Player* lastShooter_ = nullptr;

        Color3f color_;
        int type_;
};
