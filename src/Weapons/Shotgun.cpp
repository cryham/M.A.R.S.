#include "Weapons/Shotgun.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Shotgun::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    const float r = parent_->getRadius();
    const int u = 1, v = 31;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.3f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.3f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, r*-0.3f);
        uv8w(u+1, v);   glVertex2f(r*3.f, r* 0.3f);
    glEnd();
}

void Shotgun::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 1.0)
    {
        timer_ = time;
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        
        for (int i=0; i < 25; ++i)
            particles::spawn(particles::pAmmoShotgun, parent_->getLocation() + dir*parent_->getRadius(),
                dir, parent_->getVelocity(), Color3f(), parent_->getOwner());
        
        parent_->getVelocity() -= dir * 200.f;  // knock back
        sound::playSound(sound::Pump, parent_->getLocation());
    }
}


float Shotgun::maxDistance() const
{
    return 300.f;
}

float Shotgun::minDistance() const
{
    return 0.f;
}

float Shotgun::maxAngle() const
{
    return 20.f;
}
