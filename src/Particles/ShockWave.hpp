#pragma once

#include "Particles/Particle.hpp"


class ShockWave: public Particle<ShockWave>
{
    public:
        ShockWave(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<ShockWave>;

    private:
        static std::list<ShockWave*> activeParticles_;
};
