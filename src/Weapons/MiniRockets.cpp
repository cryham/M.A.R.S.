#include "Weapons/MiniRockets.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void MiniRockets::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.75f, 1.0f, 1.f);
    
    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r*-0.5f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.8f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, r*-0.8f);
        uv8w(u+1, v);   glVertex2f(r*3.f, r*-0.5f);
    glEnd();
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r*0.8f);
        uv8w(u, v+1);   glVertex2f(0,     r*0.5f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, r*0.5f);
        uv8w(u+1, v);   glVertex2f(r*3.f, r*0.8f);
    glEnd();
}

void MiniRockets::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.15f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        Vector2f side(std::cos(angleRad + M_PI_2), std::sin(angleRad + M_PI_2));

        particles::spawn(particles::pAmmoMiniRocket,
            parent_->getLocation() + 3.f * dir * parent_->getRadius() +
                                        side * parent_->getRadius() * (side_ ? -0.8f : 0.8f),
            dir, parent_->getVelocity(), Color3f(), parent_->getOwner());

        // parent_->getVelocity() -= faceDirection * 100.f;
        sound::playSound(sound::Swish, parent_->getLocation());
        ++side_;
        if (side_ >= 2)
            side_ = 0;
    }
}


float MiniRockets::maxDistance() const
{
    return 1500.f;
}

float MiniRockets::minDistance() const
{
    return 50.f;
}

float MiniRockets::maxAngle() const
{
    return 30.f;
}
