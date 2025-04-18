#include "Weapons/Fist.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Media/sound.hpp"
#include "Players/Player.hpp"
#include "Particles/particles.hpp"
#include "Menu/menus.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>


Fist::Fist(Mount* parent)
    :Weapon(weapons::wFist, parent, sf::String("FIST OF ALI"))
    ,position_(1.f)
{
    if (parent && parent->getOwner() && parent->getOwner()->team())
        color_ = parent_->getOwner()->team()->color().brightened();
    else
        color_ = Color3f::random().brightened();
}

//  draw
void Fist::draw(float alpha) const
{
    if (!menus::visible() || games::type() == games::gMenu)
    {
        float time = timer::totalTime();
        if (time - timer_ < 0.1f)
            position_ = (time - timer_) * 20.f;
        else if (time - timer_ < 0.5f)
            position_ = (0.5f - (time - timer_)) * 5.f;
        else
            position_ = 0.f;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    const float r = parent_->getRadius();

    glBegin(GL_QUADS);
        glTexCoord2f(0.109375f, 0.953125f); glVertex2f(0.f, r * 0.5f);
        glTexCoord2f(0.140625f, 0.984375f); glVertex2f(0.f, r *-0.5f);
        glTexCoord2f(0.234375f, 0.890625f); glVertex2f(position_* r*(position_+1)*1.2f, r*-0.5f * (1+position_)*0.7f);
        glTexCoord2f(0.203125f, 0.859375f); glVertex2f(position_* r*(position_+1)*1.2f, r* 0.5f * (1+position_)*0.7f);
    glEnd();

    color_.gl4f(alpha);
    const float u = 2, v = 28;
    glBegin(GL_QUADS);
        uv8w(u, v);         glVertex2f(position_*r*(position_+1),       (     r*0.5f)*(1+position_));
        uv8w(u,      v+2);  glVertex2f(position_*r*(position_+1),       (-1.f*r*0.5f)*(1+position_));
        uv8w(u+0.5f, v+2);  glVertex2f(r*(1.f+position_)*(position_+1), (-1.f*r*0.5f)*(1+position_));
        uv8w(u+0.5f, v);    glVertex2f(r*(1.f+position_)*(position_+1), (     r*0.5f)*(1+position_));
    glEnd();
}


void Fist::fire() const
{
    float time = timer::totalTime();
    if (time - timer_ > 0.5f)
    {   timer_ = time;

        float angleRad = parent_->rotation()*M_PI / 180.f;
        Vector2f dir(std::cos(angleRad), std::sin(angleRad));

        particles::spawn(particles::pAmmoFist,
            parent_->getLocation() + dir*parent_->getRadius(),
            dir, parent_->getVelocity(), Color3f(), parent_->getOwner());

        parent_->getVelocity() -= dir * 200.f;  // knock back
        sound::playSound(sound::Pump, parent_->getLocation());
    }
}


float Fist::maxDistance() const
{
    return 75.f;
}

float Fist::minDistance() const
{
    return 0.f;
}

float Fist::maxAngle() const
{
    return 10.f;
}
