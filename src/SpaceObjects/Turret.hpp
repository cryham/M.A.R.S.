#pragma once

#include "SpaceObjects/SpaceObject.hpp"
#include "Weapons/Weapon.hpp"
#include "Specials/Special.hpp"


class Turret : public SpaceObject, public Mount
{
    public:
        Turret(Vector2f const& location, float rotation, Player* owner);

        void update() override;
        void draw() const override;
        void drawWeapon() const;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        void onShockWave(Player* damageSource, float intensity) override;

        void setDamageSource(Player* evilOne) override;
        void drainLife(Player* source, float amount, Vector2f const& direction, float waitForOtherDamage = 0.001f);

        void heal(Player* source, int amount);

        float   getLife()  const;

        //  Mount:
        Vector2f velocityFake;
        Vector2f getLocation() override {  return location_;  }
        Vector2f& getVelocity() override {  return velocityFake;  }
        float    getRadius() override   {  return radius_;  }

        bool    collidable() const;
        bool    attackable() const;

        friend class Controller;
        friend class BotController;
        friend class KeyController;
        friend class CannonControl;
        friend class PowerUp;
        friend class PUHealth;
        friend class PUFuel;
        friend class ShipName;
        friend class ShipHighlight;
        friend class Tutorial;
        friend class Blast;
        friend class Freezer;
        friend class FireWall;
        friend class Shocker;
        friend class Heal;
        friend class Special;
        friend class Weapon;
        template <typename Object> friend class Ice;
        friend class Team;

    private:
        void explode();
        void respawn();

        Color3f color_;
        int graphic_;

        bool visible_;
        // float ghostTimer_;
        float frozen_;
        float respawnTimer_;
        float damageSourceResetTimer_;

        Vector2f respawnLocation_;
        float respawnRotation_;

        Weapon* weapon_ = nullptr;
        // Special* special_ = nullptr;

        float life_, maxLife_;

        float damageByLocalPlayer_;
        float damageCheckTimer_;
        Vector2f damageDirection_;
        int collisionCount_;
};
