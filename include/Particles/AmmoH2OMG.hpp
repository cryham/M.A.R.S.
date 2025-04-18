#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoH2OMG: public Particle<AmmoH2OMG>
{
    public:
        AmmoH2OMG(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoH2OMG>;

    private:
        Color3f color_;
        static std::list<AmmoH2OMG*> activeParticles_;
};
