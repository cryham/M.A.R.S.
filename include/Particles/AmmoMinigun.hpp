#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class AmmoMinigun: public Particle<AmmoMinigun>
{
    public:
        AmmoMinigun(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoMinigun();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoMinigun>;

    private:
        bool trail_;
        Color3f color_;
        static std::list<AmmoMinigun*> activeParticles_;
};
