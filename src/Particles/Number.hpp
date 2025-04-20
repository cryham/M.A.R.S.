#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Number : public Particle<Number>
{
    public:
        Number(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Number>;

    private:
        Color3f color_;
        int     value_;
        float   alpha_;
        static std::list<Number*> activeParticles_;
};
