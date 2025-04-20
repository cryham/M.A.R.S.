#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Star: public Particle<Star>
{
    public:
        Star(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void update(float time);

        void draw() const override;

        friend class Particle<Star>;

        static void init();

    private:
        Color3f  color_;
        float    depth_;
        float    alpha_;

        Vector2f acceleration_;
        static std::list<Star*> activeParticles_;
};
