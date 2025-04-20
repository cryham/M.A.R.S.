#pragma once

#include "Particles/Particle.hpp"


class HeatJet: public Particle<HeatJet>
{
    public:
        HeatJet(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<HeatJet>;

    private:
        static std::list<HeatJet*> activeParticles_;
};
