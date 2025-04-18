#include "Weapons/Flamer2.hpp"

#include "Particles/particles.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Flamer2::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.8f, 0.6f, alpha);

    const float r = parent_->getRadius();
    const int u = 0, v = 30;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,     r* 0.5f);
        uv8w(u, v+1);   glVertex2f(0,     r*-0.5f);
        uv8w(u+1, v+1); glVertex2f(r*3.f, r*-0.9f);
        uv8w(u+1, v);   glVertex2f(r*3.f, r* 0.9f);
    glEnd();
}

void Flamer2::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.01f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        for (int i=0; i < 20; ++i)
        {
            particles::spawn(particles::pAmmoFlamer2, parent_->getLocation() + dir*parent_->getRadius()*1.5f,
                dir, parent_->getVelocity(), Color3f(), parent_->getOwner());
            particles::spawn(particles::pHeatBurner, parent_->getLocation() + dir*parent_->getRadius()*1.5f,
                dir, parent_->getVelocity());
        }
        parent_->getVelocity() -= dir * 1.f;
    }
}


float Flamer2::maxDistance() const
{
    return 500.f;
}

float Flamer2::minDistance() const
{
    return 0.f;
}

float Flamer2::maxAngle() const
{
    return 10.f;
}
