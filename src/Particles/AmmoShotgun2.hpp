#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoShotgun2 : public Particle<AmmoShotgun2>
{
    public:
        AmmoShotgun2(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoShotgun2();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoShotgun2>;

    private:
        Color3f color_;
        static std::list<AmmoShotgun2*> activeParticles_;
};
