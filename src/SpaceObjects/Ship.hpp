#pragma once

#include "SpaceObjects/MobileSpaceObject.hpp"
#include "Weapons/Weapon.hpp"
#include "Specials/Special.hpp"

#define ITEM_CANNON_CONTROL 0

class Player;
class PowerUp;


class Ship : public MobileSpaceObject, public Mount
{
    public:
        Ship(Vector2f const& location, float rotation, Player* owner);

        void update() override;
        void draw() const override;
        void drawWeapon() const;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        void onShockWave(Player* damageSource, float intensity) override;

        void setDamageSource(Player* evilOne) override;
        void drainLife(Player* source, float amount, Vector2f const& direction, float waitForOtherDamage = 0.001f);

        void heal(Player* source, int amount);
        void refuel(Player* source, int amount);

        float   getLife()  const;
        float   getFuel()  const;
        Player* getOwner() const;

        //  Mount:
        Vector2f  getLocation() override {  return location_;  }
        Vector2f& getVelocity() override {  return velocity_;  }
        float     getRadius() override   {  return radius_;  }

        bool    collidable() const;  // for logic, not physics
        bool    attackable() const;

        std::vector<PowerUp*> const& getCollectedPowerUps() const;

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

        float weaponChangeTime_;
    private:

        void explode();
        void respawn();

        Player* owner_ = nullptr;

        int up_, down_, left_, right_, boost_;  // inputs

        bool docked_;
        bool weaponChange_;
        bool specialChange_;

        bool visible_;
        float ghostTimer_;
        float frozen_;
        float respawnTimer_;
        float damageSourceResetTimer_;

        Vector2f respawnLocation_;
        float respawnRotation_;

        Weapon* weapon_ = nullptr;
        Special* special_ = nullptr;
        void WeaponNext();
        void WeaponPrev();

        float life_, maxLife_;
        float fuel_, maxFuel_;

        std::vector<PowerUp*> collectedPowerUps_;

        int fragStars_;
        float damageByLocalPlayer_;
        float damageCheckTimer_;
        Vector2f damageDirection_;
        int collisionCount_;
};
