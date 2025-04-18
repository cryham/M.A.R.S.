#pragma once

#include "Particles/Particle.hpp"


class AmmoLightning: public Particle<AmmoLightning>
{
    public:
        AmmoLightning(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoLightning>;

    private:
        float spawnTime_;
        float size_;
        Color3f color_;
        static std::list<AmmoLightning*> activeParticles_;
};
