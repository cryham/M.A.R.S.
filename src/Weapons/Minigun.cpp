#include "Weapons/Minigun.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"

#include <SFML/Graphics.hpp>


void Minigun::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 0.5f, alpha);

    const float r = parent_->getRadius();
    const int u = 1, v = 31;
    glBegin(GL_QUADS);  // 1/8 / 4
        uv8w(u, v);     glVertex2f(0,      r* 0.3f);
        uv8w(u, v+1);   glVertex2f(0,      r*-0.3f);
        uv8w(u+1, v+1); glVertex2f(r*6.f,  r*-0.3f);
        uv8w(u+1, v);   glVertex2f(r*6.f,  r* 0.3f);
    glEnd();
}

void Minigun::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.02)
    {
        timer_ = time;
        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        for (int i=0; i < 3; ++i)
            particles::spawn(particles::pAmmoMinigun,
                parent_->getLocation() + dir*parent_->getRadius() + dir * 20.f,
                dir, parent_->getVelocity(), Color3f(), parent_->getOwner());

        sound::playSound(sound::LaserCollide, parent_->getLocation());
    }
}


float Minigun::maxDistance() const
{
    return 2300.f;
}

float Minigun::minDistance() const
{
    return 0.f;
}

float Minigun::maxAngle() const
{
    return 10.f;
}
