#pragma once

#include "Particles/Particle.hpp"
#include "System/Color3f.hpp"

class Ship;
class Ball;


class AmmoSeekers: public Particle<AmmoSeekers>
{
    public:
        AmmoSeekers(Vector2f const& location, Vector2f const& direction, Vector2f const& velocity,
            Color3f const& color, Player* damageSource);
        ~AmmoSeekers();

        void update() override;;
        void draw() const override;

        void onCollision(SpaceObject* with, Vector2f const& location,
                         Vector2f const& direction, Vector2f const& velocity) override;

        friend class Particle<AmmoSeekers>;
        template <typename Object> friend class Ice;
        friend class Freezer;

    private:
        Color3f color_;
        float timer_;

        Ship* shipTarget_ = nullptr;
        Ball* ballTarget_ = nullptr;
        Player* parent_ = nullptr;

        float rotation_;
        float life_;

        float frozen_;
        bool visible_;

        static std::list<AmmoSeekers*> activeParticles_;
};
