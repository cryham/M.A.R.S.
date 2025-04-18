#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoAFK85: public Particle<AmmoAFK85>
{
    public:
        AmmoAFK85(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoAFK85>;

    private:
        static std::list<AmmoAFK85*> activeParticles_;
        Color3f color_;
};
