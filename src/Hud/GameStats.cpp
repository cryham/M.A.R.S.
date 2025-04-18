#include "Hud/GameStats.hpp"

#include "System/settings.hpp"
#include "Media/text.hpp"
#include "System/timer.hpp"
#include "Particles/particles.hpp"
#include "Media/texture.hpp"

#include <SFML/OpenGL.hpp>
#include <sstream>


void GameStats::draw() const
{
    float top(20.f);

    if (settings::bShowFPS)            top += 20.f;
    if (settings::bShowParticleCount)  top += 20.f;
    // if (settings::bShowLatency)        top += 20.f;

    if (top > 20.f)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);
            // bg
            glColor4f(0.0,0.0,0.0,0.45);
            glVertex2f(5.f,15.f);
            glVertex2f(105.f,15.f);
            glVertex2f(105.f,5.f+top);
            glVertex2f(5.f,5.f+top);

            glColor4f(1.0,1.0,1.0,0.2);
            glVertex2f(5.f,15.f);
            glVertex2f(105.f,15.f);
            glColor4f(1.0,1.0,1.0,0.02);
            glVertex2f(105.f,5.f+top/4);
            glVertex2f(5.f,5.f+top/3);
        glEnd();

        glLineWidth(1.f);
        glColor4f(1.0,1.0,1.0,0.3);
        glBegin(GL_LINE_STRIP);
            glVertex2f(5.f,5.f+top);
            glVertex2f(5.f,15.f);
            glVertex2f(105.f,15.f);
            glColor4f(1.0,1.0,1.0,0.1);
            glVertex2f(105.f,15.f);
            glVertex2f(105.f,5.f+top);
            glVertex2f(5.f,5.f+top);
        glEnd();

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Interface));
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glTexCoord2f(0.8203125f, 0.03125f);  glVertex2f(20.f, 0.f);
            glTexCoord2f(0.8203125f, 0.078125f); glVertex2f(20.f, 24.f);
            glTexCoord2f(0.8359375f, 0.078125f); glVertex2f(28.f, 24.f);
            glTexCoord2f(0.8359375f, 0.03125f);  glVertex2f(28.f, 0.f);

            glTexCoord2f(0.8203125f, 0.03125f);  glVertex2f(82.f, 0.f);
            glTexCoord2f(0.8203125f, 0.078125f); glVertex2f(82.f, 24.f);
            glTexCoord2f(0.8359375f, 0.078125f); glVertex2f(90.f, 24.f);
            glTexCoord2f(0.8359375f, 0.03125f);  glVertex2f(90.f, 0.f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        top = 20.f;

        if (settings::bShowFPS)
        {
            std::stringstream sstr;
            sstr << /*"Fps: " <<*/ static_cast<int>(timer::fps() + 0.5f);
            text::drawScreenText(sf::String(sstr.str()), Vector2f(10.f,top), 12.f, TEXT_ALIGN_LEFT,
                timer::fps() > 59.f ? Color3f(0.7f, 0.72f, 0.73f) :
                timer::fps() > 30.f ? Color3f(0.8f, 0.8f, 0.3f) :
                                      Color3f(0.9f, 0.4f, 0.4f) );
            top += 20.f;
        }
        if (settings::bShowParticleCount)
        {
            if (updateTimer_ > 0.f)
                updateTimer_ -= timer::frameTime();
            else {
                particleCount_ = particles::count();
                updateTimer_ = 0.5f;
            }
            std::stringstream sstr;
            sstr << /*"Particles: " <<*/ particleCount_;
            text::drawScreenText(sf::String(sstr.str()), Vector2f(10.f,top), 12.f, TEXT_ALIGN_LEFT, Color3f(0.7f, 0.7f, 0.7f));
            top += 20.f;
        }
        /*if (settings::bShowLatency)
        {
            std::stringstream sstr;
            sstr << "Latency: " << particles::count();
            text::drawScreenText(sf::String(sstr.str()), Vector2f(10.f,top), 12.f, TEXT_ALIGN_LEFT, Color3f(0.7f, 0.7f, 0.7f));
            top += 20.f;
        }*/
    }
}
