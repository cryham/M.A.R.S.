#pragma once

#include "Particles/Particle.hpp"
#include "TrailEffects/trailEffects.hpp"


class AmmoLaser: public Particle<AmmoLaser>
{
    public:
        AmmoLaser(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoLaser();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoLaser>;

    private:
        Trail* trail_;
        const static int steps_ = 16;
        Vector2f pos_[steps_];
        static std::list<AmmoLaser*> activeParticles_;
};
