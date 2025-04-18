#include "Weapons/Shotgun2.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Shotgun2::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.5f, 1.0f, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,      r* 0.8f);
        uv8w(u, v+1);   glVertex2f(0,      r*-0.8f);
        uv8w(u+1, v+1); glVertex2f(r*2.5f, r*-0.8f);
        uv8w(u+1, v);   glVertex2f(r*2.5f, r* 0.8f);
    glEnd();
}

void Shotgun2::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.2)
    {   timer_ = time;
        
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        for (int i=0; i < 75; ++i)
            particles::spawn(particles::pAmmoShotgun2, parent_->getLocation() + dir*parent_->getRadius(),
                dir, parent_->getVelocity(), Color3f(), parent_->getOwner());

        parent_->getVelocity() -= dir * 50.f;
        sound::playSound(sound::Pump, parent_->getLocation());
    }
}


float Shotgun2::maxDistance() const
{
    return 500.f;
}

float Shotgun2::minDistance() const
{
    return 0.f;
}

float Shotgun2::maxAngle() const
{
    return 30.f;
}
