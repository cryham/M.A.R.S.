#pragma once

#include "Particles/Particle.hpp"


class BurningFragment: public Particle<BurningFragment>
{
    public:
        BurningFragment(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~BurningFragment();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<BurningFragment>;

    private:
        Color3f color_;
        float timer1_, timer2_;
        static std::list<BurningFragment*> activeParticles_;
};
