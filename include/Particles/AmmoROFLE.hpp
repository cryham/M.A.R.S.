#pragma once

#include "Particles/Particle.hpp"


class AmmoROFLE: public Particle<AmmoROFLE>
{
    public:
        AmmoROFLE(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoROFLE();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoROFLE>;

    private:
        static std::list<AmmoROFLE*> activeParticles_;
};
