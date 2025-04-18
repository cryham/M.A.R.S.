#include "Interface/ShipPreview.hpp"

#include "System/settings.hpp"
#include "System/timer.hpp"
#include "Media/texture.hpp"

#include <SFML/OpenGL.hpp>


ShipPreview::ShipPreview (Color3f* color, Color3f* teamColor, int* graphic, Vector2f const& topLeft):
    UiElement(topLeft, 20, 20),
    color_(color),
    teamColor_(teamColor),
    graphic_(graphic)
{   }

void ShipPreview::draw() const
{
    Vector2f origin = getTopLeft() + Vector2f(10.f, 10.f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(origin.x_, origin.y_, 0.f);

    glEnable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Weapons));
    teamColor_->brightened().gl4f(0.6f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.75f, 0.75f); glVertex2f(-16.f*3.2f,-16.f*3.2f);
        glTexCoord2f(0.75f, 1.f); glVertex2f(-16.f*3.2f, 16.f*3.2f);
        glTexCoord2f(1.f, 1.f); glVertex2f( 16.f*3.2f, 16.f*3.2f);
        glTexCoord2f(1.f, 0.75f); glVertex2f( 16.f*3.2f,-16.f*3.2f);
    glEnd();

    // draw ship
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRotatef(timer::totalTime()*100, 0.f, 0.f, 1.f);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ships));

    float x, y;

    x = static_cast<float>(*graphic_%8)*0.125f;
    y = static_cast<float>(std::floor(*graphic_*0.125f))*0.375f;

    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-32.f, -32.f);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-32.f,  32.f);
        glTexCoord2f(x+0.125f, y);          glVertex2f( 32.f,  32.f);
        glTexCoord2f(x, y);                 glVertex2f( 32.f, -32.f);
    glEnd();

    y += 0.125f;

    teamColor_->gl3f();
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-32.f, -32.f);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-32.f,  32.f);
        glTexCoord2f(x+0.125f, y);          glVertex2f( 32.f,  32.f);
        glTexCoord2f(x, y);                 glVertex2f( 32.f, -32.f);
    glEnd();

    y += 0.125f;

    color_->gl3f();
    glBegin(GL_QUADS);
        glTexCoord2f(x, y+0.125f);          glVertex2f(-32.f, -32.f);
        glTexCoord2f(x+0.125f, y+0.125f);   glVertex2f(-32.f,  32.f);
        glTexCoord2f(x+0.125f, y);          glVertex2f( 32.f,  32.f);
        glTexCoord2f(x, y);                 glVertex2f( 32.f, -32.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    glPopAttrib();
}
