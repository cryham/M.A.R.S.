#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class CrushedIce: public Particle<CrushedIce>
{
    public:
        CrushedIce(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<CrushedIce>;

    private:
        Color3f color_;
        static std::list<CrushedIce*> activeParticles_;
};
