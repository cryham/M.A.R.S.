#pragma once

#include "Particles/Particle.hpp"


class AmmoRifle2 : public Particle<AmmoRifle2>
{
    public:
        AmmoRifle2(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoRifle2();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoRifle2>;

    private:
        static std::list<AmmoRifle2*> activeParticles_;
};
