#include "Weapons/Rifle2.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Rifle2::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 0.4, 0.7, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 31;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.2f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.2f);
        uv8w(u+1, v+1); glVertex2f(r*6.f, r*-0.2f);
        uv8w(u+1, v);   glVertex2f(r*6.f, r* 0.2f);
    glEnd();
}

void Rifle2::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.1)
        return;
    timer_ = time;
    
    float angleRad = parent_->rotation()*M_PI / 180;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoRifle2, parent_->getLocation() + dir*parent_->getRadius(), dir,
        parent_->getVelocity(), Color3f(), parent_->getOwner());
    
    sound::playSound(sound::Sniper, parent_->getLocation());
}


float Rifle2::maxDistance() const
{
    return FLT_MAX;
}

float Rifle2::minDistance() const
{
    return 0.f;
}

float Rifle2::maxAngle() const
{
    return 5.f;
}
