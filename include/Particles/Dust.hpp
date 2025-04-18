#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Dust: public Particle<Dust>
{
    public:
        Dust(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<Dust>;

    private:
        Color3f color_;
        static std::list<Dust*> activeParticles_;
};
