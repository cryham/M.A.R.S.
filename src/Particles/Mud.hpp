#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"


class Mud: public Particle<Mud>
{
    public:
        Mud(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);

        void update() override;;
        void draw() const override;

        friend class Particle<Mud>;

    private:
        Color3f color_;
        static std::list<Mud*> activeParticles_;
};
