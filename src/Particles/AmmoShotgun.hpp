#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoShotgun : public Particle<AmmoShotgun>
{
    public:
        AmmoShotgun(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoShotgun();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoShotgun>;

    private:
        Color3f color_;
        static std::list<AmmoShotgun*> activeParticles_;
};
