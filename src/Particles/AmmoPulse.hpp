#pragma once

#include "Particles/Particle.hpp"


class AmmoPulse : public Particle<AmmoPulse>
{
    public:
        AmmoPulse(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoPulse();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<AmmoPulse>;

    private:
        float spawnTime_;
        Color3f color_;
        static std::list<AmmoPulse*> activeParticles_;
};
