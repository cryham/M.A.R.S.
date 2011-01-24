/* Heal.cpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

# include "Specials/specials.hpp"

# include "SpaceObjects/Ship.hpp"
# include "SpaceObjects/ships.hpp"
# include "Players/Player.hpp"
# include "System/timer.hpp"
# include "Players/Team.hpp"

# include <SFML/Graphics.hpp>
# include <vector>

void Heal::draw() const {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    Color3f tmp = parent_->owner_->team()->color();
    if (tmp.v() < 0.4f) tmp.v(0.4f);
    if (tmp.s() < 0.5f) tmp.s(0.5f);

    float alpha(0.6 + std::sin(timer::totalTime()*6)*0.1f);

    tmp.gl4f(alpha);

    const int posX = 1;
    const int posY = 0;

    glBegin(GL_QUADS);
        glTexCoord2f( posX*0.25f,    posY*0.25f);    glVertex2f(-parent_->radius_*4,-parent_->radius_*4);
        glTexCoord2f( posX*0.25f,   (posY+1)*0.25f); glVertex2f(-parent_->radius_*4, parent_->radius_*4);
        glTexCoord2f((posX+1)*0.25f,(posY+1)*0.25f); glVertex2f( parent_->radius_*4, parent_->radius_*4);
        glTexCoord2f((posX+1)*0.25f, posY*0.25f);    glVertex2f( parent_->radius_*4,-parent_->radius_*4);
    glEnd();

    if (timer_ > 0.f) {
        float alpha(0.f);
        if(timer_ > 0.4f)
            alpha = std::pow(0.5f-timer_,2)*100.f;
        else
            alpha = -2.5f*(0.5f-timer_)+1.25f;

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, alpha);

        const int posX = 3;
        const int posY = 3;

        glBegin(GL_QUADS);
            glTexCoord2f( posX*0.25f,    posY*0.25f);    glVertex2f(-radius_,-radius_);
            glTexCoord2f( posX*0.25f,   (posY+1)*0.25f); glVertex2f(-radius_, radius_);
            glTexCoord2f((posX+1)*0.25f,(posY+1)*0.25f); glVertex2f( radius_, radius_);
            glTexCoord2f((posX+1)*0.25f, posY*0.25f);    glVertex2f( radius_,-radius_);
        glEnd();

        timer_ -= timer::frameTime();
    }
}

void Heal::activate() const {
    if (parent_->fragStars_ > 0) {
        radius_ = parent_->fragStars_*50.f;
        std::vector<Ship*> const& ships = ships::getShips();
        for (std::vector<Ship*>::const_iterator it=ships.begin(); it!=ships.end(); ++it) {
            if ((*it)!=parent_) {
                float distance(((*it)->location_-parent_->location_).length());
                if (parent_->getOwner()->team() == (*it)->getOwner()->team() && distance <= radius_) {
                    (*it)->heal(parent_->owner_, ((radius_/distance)-0.8f)*parent_->fragStars_*10);
                    (*it)->refuel(parent_->owner_, ((radius_/distance)-0.8f)*parent_->fragStars_*10);
                }
            }
            else {
                parent_->heal(parent_->owner_, parent_->fragStars_*10);
                parent_->refuel(parent_->owner_, parent_->fragStars_*10);
            }
        }
        timer_ = 0.5f;
        parent_->fragStars_ = 0;
    }
}

void Heal::next() {
    parent_->currentSpecial_ = new Freezer(parent_);
    delete this;
}

void Heal::previous() {
    parent_->currentSpecial_ = new Blast(parent_);
    delete this;
}


