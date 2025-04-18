#include "DecoObjects/PlanetSign.hpp"

#include "SpaceObjects/Planet.hpp"
#include "System/randomizer.hpp"


PlanetSign::PlanetSign(Planet* planet):
    texture_(texture::Sign1),
    rotation_(0.f),
    scale_(randomizer::random(0.5f, 1.f))
{
    if (randomizer::random(0, 1) == 1) texture_ = texture::Sign2;

    Vector2f direction = Vector2f::randDir();
    rotation_ = std::acos(direction.x_)*180.f/M_PI + 90.f;
    if (direction.y_ < 0.f)
        rotation_ = 180.f - rotation_;

    direction = direction*(planet->radius() - scale_*0.5f);

    location_ = planet->location() + direction;
}

void PlanetSign::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(location_.x_, location_.y_, 0.f);
    glRotatef(rotation_, 0.f, 0.f, 1.f);
    glScalef(scale_, scale_, 1.f);

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture_));
    glColor3f(1,1,1);

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-100.f, -150.f);
        glTexCoord2i(0, 1); glVertex2f(-100.f,  50.f);
        glTexCoord2i(1, 1); glVertex2f( 100.f,  50.f);
        glTexCoord2i(1, 0); glVertex2f( 100.f, -150.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
