#include "Weapons/Burner.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Burner::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,      r*0.3f);
        uv8w(u, v+1);   glVertex2f(0, -1.f*r*0.3f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, -1.f*r*0.3f);
        uv8w(u+1, v);   glVertex2f(r*3.f,      r*0.3f);
    glEnd();
}

void Burner::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.05f)
    {
        timer_ = time;
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        for (int i=0; i < 20; ++i)
        {
            particles::spawn(particles::pAmmoBurner, parent_->getLocation() + dir*parent_->getRadius()*1.5f,
                dir, parent_->getVelocity(), Color3f(), parent_->getOwner());
            particles::spawn(particles::pHeatBurner, parent_->getLocation() + dir*parent_->getRadius()*1.5f,
                dir, parent_->getVelocity());
        }
        parent_->getVelocity() -= dir * 10.f;
    }
}


float Burner::maxDistance() const
{
    return 200.f;
}

float Burner::minDistance() const
{
    return 0.f;
}

float Burner::maxAngle() const
{
    return 10.f;
}
