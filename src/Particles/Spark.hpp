#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Spark : public Particle<Spark>
{
    public:
        Spark(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Spark>;

    private:
        Color3f color_;
        static std::list<Spark*> activeParticles_;
};
