#include "Weapons/OldRocket.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void OldRocket::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.5f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.5f);
        uv8w(u+1, v+1); glVertex2f(r*2.f, r*-0.5f);
        uv8w(u+1, v);   glVertex2f(r*2.f, r* 0.5f);
    glEnd();
}

void OldRocket::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 4.0f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        particles::spawn(particles::pAmmoRocket, parent_->getLocation() + dir*parent_->getRadius(), dir,
            parent_->getVelocity(), Color3f(), parent_->getOwner());
        particles::spawnMultiple(10.f, particles::pDust,  parent_->getLocation() + dir*parent_->getRadius(),
            parent_->getVelocity());
        
        parent_->getVelocity() -= dir * 400.f;  // knock back
        sound::playSound(sound::Pump, parent_->getLocation());
    }
}


float OldRocket::maxDistance() const
{
    return 500.f;
}

float OldRocket::minDistance() const
{
    return 50.f;
}

float OldRocket::maxAngle() const
{
    return 30.f;
}
