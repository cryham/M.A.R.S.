#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Fuel: public Particle<Fuel>
{
    public:
        Fuel(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Fuel>;

    private:
        Color3f color_;
        static std::list<Fuel*> activeParticles_;
};
