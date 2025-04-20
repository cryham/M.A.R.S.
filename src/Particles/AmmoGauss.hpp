#pragma once

#include "Particles/Particle.hpp"
#include "TrailEffects/trailEffects.hpp"


class AmmoGauss : public Particle<AmmoGauss>
{
    public:
        AmmoGauss(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoGauss();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoGauss>;

    private:
        Trail* trail_;
        const static int steps_ = 16;
        static std::list<AmmoGauss*> activeParticles_;
};
