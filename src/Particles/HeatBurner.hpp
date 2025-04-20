#pragma once

#include "Particles/Particle.hpp"


class HeatBurner : public Particle<HeatBurner>
{
    public:
        HeatBurner(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<HeatBurner>;

    private:
        static std::list<HeatBurner*> activeParticles_;
};
