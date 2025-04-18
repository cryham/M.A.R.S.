#pragma once

#include "Particles/Particle.hpp"


class AmmoPlasma: public Particle<AmmoPlasma>
{
    public:
        AmmoPlasma(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoPlasma();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        static void shockWave(Vector2f const& location, float strength, float radius);

        friend class Particle<AmmoPlasma>;

    private:
        Color3f color_;
        static std::list<AmmoPlasma*> activeParticles_;
};
