#pragma once

#include "Particles/Particle.hpp"


class Heat: public Particle<Heat>
{
    public:
        Heat(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Heat>;

    private:
        static std::list<Heat*> activeParticles_;
};
