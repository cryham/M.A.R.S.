#include "SpaceObjects/stars.hpp"

#include "Media/texture.hpp"
#include "System/settings.hpp"
#include "System/window.hpp"
#include "Particles/particles.hpp"
#include "Particles/Star.hpp"
#include "defines.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>

namespace stars
{
    namespace
    {
        int tex_;
        float top_, left_;
        float spawnTimer_(0.f);
    }

    void init()
    {
        tex_ = randomizer::random(0, 1);
        top_ = randomizer::random(0.f, 1.f);
        left_= randomizer::random(0.f, 1.f);
        Star::init();
    }

    void draw()
    {
        glDisable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);

        if (settings::bStarsHigh)
            switch (tex_)
            {
                case 0: glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Stars1_large)); break;
                case 1: glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Stars2_large)); break;
            }
        else
            switch (tex_)
            {
                case 0: glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Stars1_medium)); break;
                case 1: glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Stars2_medium)); break;
            }

        Vector2f const& viewport = window::getViewPort();
        const float res = settings::bStarsHigh ? 1.f/2048.f : 1.f/1024.f;

        glBegin(GL_QUADS);
            glColor3f(1.f, 1.0f, 1.0f);
            glTexCoord2f(left_,                   top_);                   glVertex2f(0, 0);
            glTexCoord2f(left_,                   top_ + res*viewport.y_); glVertex2f(0, viewport.y_);
            glTexCoord2f(left_ + res*viewport.x_, top_ + res*viewport.y_); glVertex2f(viewport.x_, viewport.y_);
            glTexCoord2f(left_ + res*viewport.x_, top_);                   glVertex2f(viewport.x_, 0);
        glEnd();

        glEnable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
