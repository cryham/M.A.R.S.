/* ShipName.cpp

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

# include "DecoObjects/ShipName.hpp"

# include "SpaceObjects/Ship.hpp"
# include "Players/Player.hpp"
# include "Media/text.hpp"
# include "System/settings.hpp"

# include <sstream>

void ShipName::draw() const {
    if (ship_->visible_) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        if (ship_->weaponChange_ && ((ship_->owner_->type() == controllers::cPlayer1) | (ship_->owner_->type() == controllers::cPlayer2)))
            text::drawSpaceText(ship_->currentWeapon_->getName(), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f, 12.f, TEXT_ALIGN_CENTER, Color3f(0.8f, 0.8f, 0.8f));
        else if (ship_->specialChange_ && ((ship_->owner_->type() == controllers::cPlayer1) | (ship_->owner_->type() == controllers::cPlayer2)))
            text::drawSpaceText(ship_->currentSpecial_->getName(), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f, 12.f, TEXT_ALIGN_CENTER, Color3f(0.8f, 0.8f, 0.8f));
        else {
            Color3f color(1.f, 0.f, 0.f);
            color.h(color.h() + ship_->getLife());

            if (ship_->docked_)
                text::drawSpaceText(ship_->owner_->name(), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f, 12.f, TEXT_ALIGN_CENTER, color);
            else
                text::drawMobileSpaceText(ship_->owner_->name(), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f, 12.f, TEXT_ALIGN_CENTER, color);
        }

        if (ship_->fragStars_ > 0) {

            Color3f color(1.0f, 0.5f, 0.7f);

            std::stringstream sstr;
            for (int i=0; i<ship_->fragStars_; ++i)
                sstr << "*";
            if (ship_->docked_)
                text::drawSpaceText(sf::String(sstr.str()), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f + Vector2f(0.f, -17.f), 25.f, TEXT_ALIGN_CENTER, color);
            else
                text::drawMobileSpaceText(sf::String(sstr.str()), ship_->location_ + Vector2f(0.f, -ship_->radius_)*2.5f + Vector2f(0.f, -17.f), 25.f, TEXT_ALIGN_CENTER, color);
        }
    }
}
