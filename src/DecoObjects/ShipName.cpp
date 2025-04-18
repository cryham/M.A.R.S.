#include "DecoObjects/ShipName.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Media/text.hpp"
#include "System/settings.hpp"
#include "System/window.hpp"
#include "Weapons/weapons.hpp"

#include <GL/gl.h>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <sstream>


void ShipName::draw() const
{
    if (!ship_->visible_)
        return;

    float r = -ship_->radius_ * 2.5f *
        (1.f + 0.002f * ship_->location_.y_);  // fix offset?
    float life = ship_->getLife();

    bool player = ship_->owner_->type() == controllers::cPlayer1 ||
        ship_->owner_->type() == controllers::cPlayer2;
    
    if (player && (ship_->weaponChange_ || ship_->weaponChangeTime_ > 0.f))
        text::drawSpaceText(ship_->weapon_->getName(),
                            ship_->location_ + Vector2f(0.f, r),
                            12.f, TEXT_ALIGN_CENTER,
                            weapons::colors[ship_->weapon_->getType()]);
    else
    if (player && ship_->specialChange_)
        text::drawSpaceText(ship_->special_->getName(),
                            ship_->location_ + Vector2f(0.f, r),
                            12.f, TEXT_ALIGN_CENTER, Color3f(0.8f, 0.8f, 1.f));
    else
    {   Color3f color(1.f, 0.f, 0.f);
        color.h(color.h() + life);

        if (ship_->docked_)
            text::drawSpaceText(ship_->owner_->name(),
                ship_->location_ + Vector2f(0.f, r), 12.f, TEXT_ALIGN_CENTER, color);
        else
            text::drawMobileSpaceText(ship_->owner_->name(),
                ship_->location_ + Vector2f(0.f, r), 12.f, TEXT_ALIGN_CENTER, color);
    }
    
    if (bar_)  // ----
    {
        glBegin(GL_QUADS);
            Color3f color(1.f, 0.f, 0.f);
            color.h(color.h() + life);
            color.gl4f(0.6);
            Vector2f pos(window::coordToPixel(ship_->location()));

            const float y = -2.f, y2 = y + 8.f;
            glVertex2f(pos.x_-20.f, pos.y_ + r + y2);
            glVertex2f(pos.x_-20.f + life*0.4f, pos.y_ + r + y2);
            glVertex2f(pos.x_-20.f + life*0.4f, pos.y_ + r + y);
            glVertex2f(pos.x_-20.f, pos.y_ + r + y);
        glEnd();
    }

    if (ship_->fragStars_ > 0)
    {
        Color3f color(1.0f, 0.7f, 0.5f);

        std::stringstream sstr;
        int stars = std::min(6, ship_->fragStars_);  // max stars
        for (int i=0; i < stars; ++i)
            sstr << "*";
        if (ship_->docked_)
            text::drawSpaceText(sf::String(sstr.str()),
            ship_->location_ + Vector2f(0.f, r) + Vector2f(0.f, -17.f), 25.f, TEXT_ALIGN_CENTER, color);
        else
            text::drawMobileSpaceText(sf::String(sstr.str()),
            ship_->location_ + Vector2f(0.f, r) + Vector2f(0.f, -17.f), 25.f, TEXT_ALIGN_CENTER, color);
    }

    /*std::stringstream sstr;
    sstr << static_cast<int>(life) << "%";
    Color3f color(1.f, 0.f, 0.f);
    color.h(color.h() + life);
    text::drawMobileSpaceText(sstr.str(), ship_->location_ + Vector2f(-15.f, r + 15.f), 9.f, TEXT_ALIGN_CENTER, color);
    sstr.str("");
    sstr << static_cast<int>(ship_->getFuel()) << "%";
    color = Color3f(1.f, 0.f, 0.f);
    color.h(color.h() + ship_->getFuel());
    text::drawMobileSpaceText(sstr.str(), ship_->location_ + Vector2f( 15.f, r + 15.f), 9.f, TEXT_ALIGN_CENTER, color);*/

    /*Vector2f shipLocation(window::coordToPixel(ship_->location()));
    glLineWidth(2.f);
    glBegin(GL_LINES);
        Color3f color(1.f, 0.f, 0.f);
        color.h(color.h() + life);
        color.gl4f(0.5);

        glVertex2f(shipLocation.x_-20.f, shipLocation.y_ r + 25.f);
        glVertex2f(shipLocation.x_-20.f + life*0.4f, shipLocation.y_ r + 25.f);

        color = Color3f(1.f, 0.8f, 0.f);
        //color.h(color.h() + ship_->getFuel());
        color.gl4f(0.3);

        glVertex2f(shipLocation.x_-20.f, shipLocation.y_ r + 28.f);
        glVertex2f(shipLocation.x_-20.f + ship_->getFuel()*0.4f, shipLocation.y_ - ship_->radius_*2.5f + 28.f);
    glEnd();*/
}
