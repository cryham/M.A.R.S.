#pragma once

#include "System/Vector2f.hpp"
#include "System/Color3f.hpp"
#include "Items/items.hpp"

#include <list>

class Ship;


//  Base for all collectible power ups

class PowerUp
{
    public:
        PowerUp(items::PowerUpType type, Vector2f const& location, float radius,
                float totalLifeTime, int texX, int texY, Color3f const& bgColor);

        virtual ~PowerUp();

        virtual void update();
        virtual void draw() const;

        Vector2f const& location() const;
        float           radius()   const;
        items::PowerUpType type()  const;

        bool isDead()              const;
        bool isCollected()         const;

    protected:
        virtual void refreshLifeTime() = 0;

        Vector2f location_;
        float radius_;

        std::list<Ship*> ships_;
        bool collected_;

        items::PowerUpType type_;
        float lifeTime_, totalLifeTime_;

    private:
        int texX_, texY_;
        Color3f bgColor_;
};
