#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"

class Ship;
class Ball;


class AmmoMiniRocket : public Particle<AmmoMiniRocket>
{
    public:
        AmmoMiniRocket(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoMiniRocket();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoMiniRocket>;
        template <typename Object> friend class Ice;
        friend class Freezer;

    private:
        Color3f color_;
        float timer_;

        Player* parent_;

        float rotation_;
        float life_;

        float frozen_;
        bool visible_;

        static std::list<AmmoMiniRocket*> activeParticles_;
};
