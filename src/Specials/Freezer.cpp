#include "Specials/Freezer.hpp"

#include "Particles/AmmoRocket.hpp"
#include "SpaceObjects/Ship.hpp"
#include "SpaceObjects/ships.hpp"
#include "SpaceObjects/balls.hpp"
#include "Players/Player.hpp"
#include "System/timer.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Teams/Team.hpp"
#include "Items/items.hpp"

#include <SFML/Graphics.hpp>
#include <vector>


void Freezer::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    parent_->getOwner()->team()->color().brightened().gl4f(0.8f*alpha);;

    const float r = parent_->getRadius();
    const int u = 2, v = 0;

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

        float scale(1.f-timer_);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        const int u = 2, v = 1;

        glBegin(GL_QUADS);
            uv4(u, v);     glVertex2f(-radius_*scale,-radius_*scale);
            uv4(u, v+1);   glVertex2f(-radius_*scale, radius_*scale);
            uv4(u+1, v+1); glVertex2f( radius_*scale, radius_*scale);
            uv4(u+1, v);   glVertex2f( radius_*scale,-radius_*scale);
        glEnd();

        if (!menus::visible() || games::type() == games::gMenu)
            timer_ -= timer::frameTime()*2.f;
    }
}

void Freezer::activate() const
{
    if (parent_->fragStars_ > 0 && timer_ <= 0.f)
    {
        radius_ = radius();
        const float strength = parent_->fragStars_*14.f;

        std::vector<Ship*> const& ships = ships::getShips();
        for (auto& it : ships)
        {
            if (it != parent_ && it->collidable() && !it->collectedPowerUps_[items::puShield])
            {
                float distance((it->location()-parent_->getLocation()).length());
                if (distance <= radius_)
                {
                    it->setDamageSource(parent_->getOwner());
                    it->velocity_=Vector2f();
                    it->mass_ = 9999999999.f;
                    
                    if (it->frozen_ <= 0)
                        decoObjects::addIce(it);
                    it->frozen_= strength;
                }
            }
        }
        Ball* ball = balls::getBall();

        if (ball && ball->visible_)
        {
            float distance((ball->location()-parent_->getLocation()).length());
                if (distance <= radius_)
                {
                    ball->velocity_=Vector2f();
                    ball->mass_ = 9999999999.f;
                    
                    if (ball->frozen_ <= 0)
                        decoObjects::addIce(ball);
                    ball->frozen_=strength;
            }
        }

        for (auto& it : AmmoRocket::activeParticles_)
        {
            float distance((it->location()-parent_->getLocation()).length());
            if (distance <= radius_)
            {
                it->velocity_ = it->velocity_*0.00001f;
                it->mass_ = 9999999999.f;
                
                if (it->frozen_ <= 0)
                    decoObjects::addIce(it);
                it->frozen_=strength;
            }
        }

        timer_ = 0.5f;
        parent_->fragStars_ = 0;
    }
}

float Freezer::radius() const
{
    return (parent_->fragStars_ > 0 ? parent_->fragStars_*50.f+150.f : 0.f);
}
