#include "Weapons/Insta.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Particles/particles.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "System/Color3f.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>
#include <cfloat>


Insta::Insta(Mount* parent)
    :Weapon(weapons::wInsta, parent, sf::String("INSTA-GRAVE"))
{
    if (parent && parent->getOwner() && parent->getOwner()->team())
        color_ = parent_->getOwner()->team()->color().brightened();
    else
        color_ = Color3f::random().brightened();
}

void Insta::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color_.gl4f(alpha);

    const float r = parent_->getRadius();
    const int u = 2, v = 31;
    glBegin(GL_QUADS);
        uv8w(u, v);     glVertex2f(0,      r* 0.2f);
        uv8w(u, v+1);   glVertex2f(0,      r*-0.2f);
        uv8w(u+1, v+1); glVertex2f(r*4.5f, r*-0.2f);
        uv8w(u+1, v);   glVertex2f(r*4.5f, r* 0.2f);
    glEnd();
}

void Insta::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 3.0)
    {   timer_ = time;
    
        float angleRad = parent_->rotation()*M_PI / 180;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        
        particles::spawn(particles::pAmmoInsta, parent_->getLocation() + dir*parent_->getRadius(), dir,
            parent_->getVelocity(), color_, parent_->getOwner());
        
        sound::playSound(sound::Sniper, parent_->getLocation());
    }
}


float Insta::maxDistance() const
{
    return FLT_MAX;
}

float Insta::minDistance() const
{
    return 500.f;
}

float Insta::maxAngle() const
{
    return 30.f;
}
