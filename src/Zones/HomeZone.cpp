#include "Zones/HomeZone.hpp"

#include "SpaceObjects/SpaceObject.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/players.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"
#include "defines.hpp"
#include "System/settings.hpp"

#include <cmath>


HomeZone::HomeZone(Vector2f const& location) :
    radius_(450.f),
    location_(location)
{
    if (location_.x_ < settings::iMapXsize*0.5f)
        homeSide_ = 0;
    else
        homeSide_ = 1;
}

bool HomeZone::isInside(SpaceObject const& toBeChecked) const
{
    return((toBeChecked.location() - location_).lengthSquare() <= radius_*radius_);
}

void HomeZone::draw() const
{
    glColor4f(0.f, 0.f, 0.f, 0.f);

    glBlendFunc(GL_ONE, GL_ONE);
    glBegin(GL_TRIANGLE_FAN);
         glVertex2f(location_.x_, location_.y_);
         glColor4f(0.f, 0.f, 0.7f, 0.3f);
         for (double i=0; i <= 2*M_PI; i += M_PI*0.02)
            glVertex2f( location_.x_ + std::sin(i) * radius_, location_.y_ + std::cos(i) * radius_);
    glEnd();
}
