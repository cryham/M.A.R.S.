#include "Specials/Blast.hpp"

#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/ships.hpp"
#include "Players/Player.hpp"
#include "System/timer.hpp"
#include "SpaceObjects/physics.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>


void Blast::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    parent_->getOwner()->team()->color().brightened().gl4f(0.8f*alpha);

    float scale(4 + std::sin(timer::totalTime()*6)*0.3f);
    const float r = parent_->getRadius();
    const int u = 0, v = 0;

    glBegin(GL_QUADS);
        uv4(u, v);     glVertex2f(-r*scale,-r*scale);
        uv4(u, v+1);   glVertex2f(-r*scale, r*scale);
        uv4(u+1, v+1); glVertex2f( r*scale, r*scale);
        uv4(u+1, v);   glVertex2f( r*scale,-r*scale);
    glEnd();

    // draw effect
    if (timer_ > 0.f)
    {
        if (parent_->getLife() <= 0.f)
            timer_ = 0.f;

        float alpha(0.f);
        if (timer_ > 0.4f)
            alpha = std::pow(0.5f-timer_,2)*100.f;
        else
            alpha = -2.5f*(0.5f-timer_)+1.25f;

        float scale(1.f-timer_*2.f);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        const int u = 0, v = 1;

        glBegin(GL_QUADS);
            uv4(u, v);     glVertex2f(-radius_*scale,-radius_*scale);
            uv4(u, v+1);   glVertex2f(-radius_*scale, radius_*scale);
            uv4(u+1, v+1); glVertex2f( radius_*scale, radius_*scale);
            uv4(u+1, v);   glVertex2f( radius_*scale,-radius_*scale);
        glEnd();

        if (!menus::visible() || games::type() == games::gMenu)
            timer_ -= timer::frameTime();
    }
}

void Blast::activate() const
{
    if (parent_->fragStars_ > 0  && timer_ <= 0.f)
    {
        radius_ = radius();
        parent_->fragStars_ = 0;
        physics::causeShockWave(parent_->getOwner(), parent_->getLocation(), 1000.f, radius_*0.8f, 0.f);
        timer_ = 0.5f;
    }
}

float Blast::radius() const
{
    return parent_->fragStars_ > 0 ?
        parent_->fragStars_ * 150.f + 150.f : 0.f;
}
