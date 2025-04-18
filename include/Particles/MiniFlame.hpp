#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class MiniFlame: public Particle<MiniFlame>
{
    public:
        MiniFlame(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<MiniFlame>;

    private:
        Color3f color_;
        float flickerSpeed_, timer_;
        static std::list<MiniFlame*> activeParticles_;
};
