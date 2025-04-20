#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Fragment: public Particle<Fragment>
{
    public:
        Fragment(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Fragment>;

    private:
        Color3f color_;
        static std::list<Fragment*> activeParticles_;
};
