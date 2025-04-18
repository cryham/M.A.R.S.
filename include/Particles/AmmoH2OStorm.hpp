#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoH2OStorm: public Particle<AmmoH2OStorm>
{
    public:
        AmmoH2OStorm(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoH2OStorm>;

    private:
        int index_;
        Color3f color_;
        static std::list<AmmoH2OStorm*> activeParticles_;
};
