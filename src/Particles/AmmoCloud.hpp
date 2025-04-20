#pragma once

#include "Particles/Particle.hpp"


class AmmoCloud : public Particle<AmmoCloud>
{
    public:
        AmmoCloud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoCloud();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<AmmoCloud>;

    private:
        float spawnTime_;
        Color3f color_;
        static std::list<AmmoCloud*> activeParticles_;
};
