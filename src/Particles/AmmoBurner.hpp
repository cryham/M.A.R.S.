#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoBurner: public Particle<AmmoBurner>
{
    public:
        AmmoBurner(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoBurner>;

    private:
        Color3f color_;
        static std::list<AmmoBurner*> activeParticles_;
};
