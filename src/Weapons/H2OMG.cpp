#include "Weapons/H2OMG.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


void H2OMG::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.7f, 0.7f, 1.f);

    const float r = parent_->getRadius();
    const int u = 0, v = 29;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.4f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.4f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, r*-0.4f);
        uv8w(u+1, v);   glVertex2f(r*3.f, r* 0.4f);
    glEnd();
}

void H2OMG::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.1f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        
        particles::spawn(particles::pAmmoH2OMG, parent_->getLocation() + dir*parent_->getRadius()*1.5, dir,
            parent_->getVelocity(), Color3f(), parent_->getOwner());
        particles::spawn(particles::pAmmoH2OMG, parent_->getLocation() + dir*parent_->getRadius(), dir,
            parent_->getVelocity(), Color3f(), parent_->getOwner());

        parent_->getVelocity() -= dir * 20.f;
        sound::playSound(sound::BlubPop, parent_->getLocation());
    }
}


float H2OMG::maxDistance() const
{
    return FLT_MAX;
}

float H2OMG::minDistance() const
{
    return 0.f;
}

float H2OMG::maxAngle() const
{
    return 20.f;
}
