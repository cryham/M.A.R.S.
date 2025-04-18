#include "Weapons/Laser.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Laser::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0, 1.2, 0.2, 1.f); //alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 31;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.2f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.2f);
        uv8w(u+1, v+1); glVertex2f(r*9.f, r*-0.2f);
        uv8w(u+1, v);   glVertex2f(r*9.f, r* 0.2f);
    glEnd();
}

void Laser::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.01)
        return;
    timer_ = time;
    float angleRad = parent_->rotation()*M_PI / 180;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoLaser, parent_->getLocation() + dir*parent_->getRadius(), dir,
        parent_->getVelocity(), Color3f(), parent_->getOwner());
    
    //sound::playSound(sound::Check, parent_->getLocation());
}


float Laser::maxDistance() const
{
    return 1500.f;
}

float Laser::minDistance() const
{
    return 0.f;
}

float Laser::maxAngle() const
{
    return 5.f;
}
