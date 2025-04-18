
#include "Zones/TutorialZone.hpp"

#include "SpaceObjects/SpaceObject.hpp"
#include "SpaceObjects/spaceObjects.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Players/players.hpp"
#include "Players/Player.hpp"
#include "Teams/Team.hpp"
#include <SFML/System.hpp>

#include <cmath>


TutorialZone::TutorialZone(Vector2f const& location, float radius) :
    radius_(radius),
    location_(location)
{   }

bool TutorialZone::isInside(SpaceObject const& toBeChecked) const
{
    return (toBeChecked.location()-location_).lengthSquare() <= radius_*radius_*0.7f;
}

void TutorialZone::draw() const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBegin(GL_TRIANGLE_FAN);
         glColor4f(1.f, 0.5f, 0.8f, (std::sin(timer::totalTime()*2.f) + 1.f) * 0.3f + 0.4f);
         glVertex2f(location_.x_, location_.y_);
         glColor4f(1.f, 0.5f, 0.8f, 0.f);
         for (double i=0; i <= 2*M_PI; i += M_PI*0.02)
            glVertex2f( location_.x_ + std::sin(i) * radius_, location_.y_ + std::cos(i) * radius_);
    glEnd();
}
