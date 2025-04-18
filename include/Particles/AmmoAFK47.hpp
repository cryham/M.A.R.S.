#pragma once

#include "Particles/Particle.hpp"


class AmmoAFK47: public Particle<AmmoAFK47>
{
    public:
        AmmoAFK47(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoAFK47>;

    private:
        static std::list<AmmoAFK47*> activeParticles_;
};
