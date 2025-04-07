/* TeamZone.cpp

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

#include "Zones/TeamZone.hpp"
#include "SpaceObjects/SpaceObject.hpp"
#include "defines.hpp"
#include "System/settings.hpp"


bool TeamZone::isInside(SpaceObject const& toBeChecked) const
{
    switch (homeSide_)
    {
        case 0:    return toBeChecked.location().x_ < settings::C_MapXsize*0.5f;
        case 1:    return toBeChecked.location().x_ > settings::C_MapXsize*0.5f;
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
                glVertex2f(0.f, settings::C_MapYsize);
                glColor4f (0.f, 0.7f, 0.f, 0.3f);
                glVertex2f(settings::C_MapXsize*0.5f-1, settings::C_MapYsize);
                glVertex2f(settings::C_MapXsize*0.5f-1, 0.f);
            glEnd();
            break;
        case 1:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBegin(GL_QUADS);
                glColor4f (0.f, 0.7f, 0.f, 0.3f);
                glVertex2f(settings::C_MapXsize*0.5f-1, 0.f);
                glVertex2f(settings::C_MapXsize*0.5f-1, settings::C_MapYsize);
                glColor4f (0.f, 0.7f, 0.f, 0.f);
                glVertex2f(settings::C_MapXsize, settings::C_MapYsize);
                glVertex2f(settings::C_MapXsize, 0.f);
            glEnd();
            break;
        default :;
    }
}
