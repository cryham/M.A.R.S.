#pragma once

#include "Particles/Particle.hpp"


class MiniFlameSmoke: public Particle<MiniFlameSmoke>
{
    public:
        MiniFlameSmoke(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<MiniFlameSmoke>;

    private:
        Color3f color_;
        static std::list<MiniFlameSmoke*> activeParticles_;
};
