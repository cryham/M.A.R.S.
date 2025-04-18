#include "Weapons/Cloud.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void Cloud::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.6f, 0.6f, 1.f);

    const float r = parent_->getRadius();
    const int u = 0, v = 29;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 1.5f);
        uv8w(u, v+1);   glVertex2f(0,     r*-1.5f);
        uv8w(u+1, v+1); glVertex2f(r*5.f, r*-1.5f);
        uv8w(u+1, v);   glVertex2f(r*5.f, r* 1.5f);
    glEnd();
}

void Cloud::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ <= 0.2f)
        return;
    timer_ = time;

    float angleRad = parent_->rotation()*M_PI / 180.f;
    Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    particles::spawn(particles::pAmmoCloud,
        parent_->getLocation() + dir*parent_->getRadius(),
        dir, parent_->getVelocity(), Color3f(), parent_->getOwner());
    
    parent_->getVelocity() -= dir * 10.f;
    sound::playSound(sound::Blub, parent_->getLocation());
}


float Cloud::maxDistance() const
{
    return FLT_MAX;
}

float Cloud::minDistance() const
{
    return 20.f;
}

float Cloud::maxAngle() const
{
    return 50.f;
}
