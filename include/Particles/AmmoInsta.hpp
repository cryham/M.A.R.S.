#pragma once

#include "Particles/Particle.hpp"

class Trail;
class Team;


class AmmoInsta: public Particle<AmmoInsta>
{
    public:
        AmmoInsta(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoInsta();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        static int hitsAny(Vector2f const& location, Vector2f const& direction, Team* team);

        friend class Particle<AmmoInsta>;

    private:
        static std::list<AmmoInsta*> activeParticles_;
        Trail* trail_;
        Color3f color_;
};
