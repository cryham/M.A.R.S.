#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class PowerUpCollect : public Particle<PowerUpCollect>
{
    public:
        PowerUpCollect(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<PowerUpCollect>;

    private:
        Color3f color_;
        int const texX_;
        int const texY_;
        static std::list<PowerUpCollect*> activeParticles_;
};
