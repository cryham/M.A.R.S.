#pragma once

#include "Particles/Particle.hpp"


class CannonBall : public Particle<CannonBall>
{
    public:
        CannonBall(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<CannonBall>;

    private:
        float timer1_, timer2_;
        static std::list<CannonBall*> activeParticles_;
};
