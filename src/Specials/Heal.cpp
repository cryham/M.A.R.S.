#include "Specials/Heal.hpp"

#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/ships.hpp"
#include "Players/Player.hpp"
#include "System/timer.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>
#include <vector>


void Heal::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    alpha *= 0.6 + std::sin(timer::totalTime()*6)*0.1f;
    parent_->getOwner()->team()->color().brightened().gl4f(alpha);

    const float r = parent_->getRadius();
    const int u = 1, v = 0;

    glBegin(GL_QUADS);
        uv4(u, v);     glVertex2f(-r*4,-r*4);
        uv4(u, v+1);   glVertex2f(-r*4, r*4);
        uv4(u+1, v+1); glVertex2f( r*4, r*4);
        uv4(u+1, v);   glVertex2f( r*4,-r*4);
    glEnd();

    if (timer_ > 0.f)
    {
        float alpha(0.f);
        if (timer_ > 0.4f)
            alpha = std::pow(0.5f-timer_,2)*100.f;
        else
            alpha = -2.5f*(0.5f-timer_)+1.25f;

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        const int u = 1, v = 1;

        glBegin(GL_QUADS);
            uv4(u, v);     glVertex2f(-radius_,-radius_);
            uv4(u, v+1);   glVertex2f(-radius_, radius_);
            uv4(u+1, v+1); glVertex2f( radius_, radius_);
            uv4(u+1, v);   glVertex2f( radius_,-radius_);
        glEnd();

        if (!menus::visible() || games::type() == games::gMenu)
            timer_ -= timer::frameTime();
    }
}


void Heal::activate() const
{
    if (parent_->fragStars_ > 0  && timer_ <= 0.f)
    {
        radius_ = radius();
        const auto& ships = ships::getShips();
        for (const auto& it : ships)
        {
            if (it != parent_)
            {
                float distance((it->location()-parent_->getLocation()).length());
                if (it->collidable() && parent_->getOwner()->team() == it->getOwner()->team() && distance <= radius_)
                {
                    it->heal(  parent_->getOwner(), ((radius_/distance)-0.8f)*parent_->fragStars_*30);
                    it->refuel(parent_->getOwner(), ((radius_/distance)-0.8f)*parent_->fragStars_*30);
                }
            }else
            {
                parent_->heal(  parent_->getOwner(), parent_->fragStars_*30);
                parent_->refuel(parent_->getOwner(), parent_->fragStars_*30);
            }
        }
        timer_ = 0.5f;
        parent_->fragStars_ = 0;
    }
}

float Heal::radius() const
{
    return (parent_->fragStars_ > 0 ? parent_->fragStars_*50.f+50.f : 0.f);
}
