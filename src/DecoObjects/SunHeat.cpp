#include "DecoObjects/SunHeat.hpp"

#include "SpaceObjects/Sun.hpp"
#include "System/timer.hpp"


SunHeat::SunHeat(Sun* sun):
    location_(sun->location()),
    radius_(sun->radius())
{   }

void SunHeat::draw() const
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(location_.x_, location_.y_, 0);
    float rotation(timer::totalTime()*25.f);
    glRotatef(rotation, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::SunHeat));

    glColor4f(1,1,1,0.6);
    float drawRadius = radius_*2.f;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-drawRadius, -drawRadius);
        glTexCoord2i(0, 1); glVertex2f(-drawRadius,  drawRadius);
        glTexCoord2i(1, 1); glVertex2f( drawRadius,  drawRadius);
        glTexCoord2i(1, 0); glVertex2f( drawRadius, -drawRadius);
    glEnd();
    glColor4f(1,1,1,0.6);
    glRotatef(rotation*-2, 0, 0, 1);
    drawRadius = radius_*2.0f;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-drawRadius, -drawRadius);
        glTexCoord2i(0, 1); glVertex2f(-drawRadius,  drawRadius);
        glTexCoord2i(1, 1); glVertex2f( drawRadius,  drawRadius);
        glTexCoord2i(1, 0); glVertex2f( drawRadius, -drawRadius);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}


