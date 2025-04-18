#include "DecoObjects/Evil.hpp"

#include "Media/texture.hpp"
#include "System/timer.hpp"
#include "defines.hpp"
#include "System/settings.hpp"

#include <SFML/OpenGL.hpp>


void Evil::draw() const
{
    if (!settings::bLogoSigns)
        return;

    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::CannonSocket));
    glColor3f(1,1,1);
    glTranslatef(settings::iMapXsize*0.5f+210.f, -100.f, 0.f);
    glRotatef(std::sin(timer::totalTime())*5.f, 0.f, 0.f, 1.f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.5f); glVertex2f(-50.f, 90.f);
        glTexCoord2f(0.f, 0.95f); glVertex2f(-50.f, 180.f);
        glTexCoord2f(0.5f, 0.95f); glVertex2f( 50.f, 180.f);
        glTexCoord2f(0.5f, 0.5f); glVertex2f( 50.f, 90.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
