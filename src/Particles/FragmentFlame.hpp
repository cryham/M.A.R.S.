#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class FragmentFlame : public Particle<FragmentFlame>
{
    public:
        FragmentFlame(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<FragmentFlame>;

    private:
        Color3f color_;
        static std::list<FragmentFlame*> activeParticles_;
};
