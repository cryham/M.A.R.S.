#include "Zones/TeamZone.hpp"
#include "SpaceObjects/SpaceObject.hpp"
#include "defines.hpp"
#include "System/settings.hpp"


bool TeamZone::isInside(SpaceObject const& toBeChecked) const
{
    switch (homeSide_)
    {
        case 0:    return toBeChecked.location().x_ < settings::iMapXsize*0.5f;
        case 1:    return toBeChecked.location().x_ > settings::iMapXsize*0.5f;
        default:   return false;
    }
}

void TeamZone::draw() const
{
    switch (homeSide_)
    {
        case 0:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBegin(GL_QUADS);
                glColor4f (0.f, 0.7f, 0.f, 0.f);
                glVertex2f(0.f, 0.f);
                glVertex2f(0.f, settings::iMapYsize);
                glColor4f (0.f, 0.7f, 0.f, 0.3f);
                glVertex2f(settings::iMapXsize*0.5f-1, settings::iMapYsize);
                glVertex2f(settings::iMapXsize*0.5f-1, 0.f);
            glEnd();
            break;
        case 1:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBegin(GL_QUADS);
                glColor4f (0.f, 0.7f, 0.f, 0.3f);
                glVertex2f(settings::iMapXsize*0.5f-1, 0.f);
                glVertex2f(settings::iMapXsize*0.5f-1, settings::iMapYsize);
                glColor4f (0.f, 0.7f, 0.f, 0.f);
                glVertex2f(settings::iMapXsize, settings::iMapYsize);
                glVertex2f(settings::iMapXsize, 0.f);
            glEnd();
            break;
        default :;
    }
}
