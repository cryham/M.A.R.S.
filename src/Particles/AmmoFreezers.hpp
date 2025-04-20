#pragma once

#include "Particles/Particle.hpp"


class AmmoFreezers : public Particle<AmmoFreezers>
{
    public:
        AmmoFreezers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoFreezers();

        void update() override;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoFreezers>;

    private:
        float spawnTime_;
        Color3f color_;
        static std::list<AmmoFreezers*> activeParticles_;
};
