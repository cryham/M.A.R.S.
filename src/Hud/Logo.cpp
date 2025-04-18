#include "Hud/Logo.hpp"

#include "Media/texture.hpp"
#include "System/window.hpp"
#include "Games/games.hpp"
#include "System/timer.hpp"
#include "defines.hpp"
#include "System/settings.hpp"
#include "System/randomizer.hpp"


Logo::Logo():
    timer_(1.f),
    on_(false),
    flicCount_(1)
{   }

void Logo::update()
{
    if (games::elapsedTime() < 5.f)
        on_ =  randomizer::random(15, 25)*games::elapsedTime() > 50 && randomizer::random(0, 1000) < 990;
    else
    {
        if (timer_ < 0.f)
        {
            on_ = !on_;
            if (flicCount_-- == 0)
                flicCount_ = randomizer::random(1, 19);
            if (on_)
            {
                if (flicCount_ > 0)
                    timer_ = randomizer::random(0.01f, 0.05f);
                else
                    timer_ = randomizer::random(0.01f, 5.f);
            }else
            {
                if (flicCount_ > 0)
                    timer_ = randomizer::random(0.01f, 0.01f);
                else
                    timer_ = randomizer::random(0.01f, 1.f);
            }
        }else
            timer_ -= timer::frameTime();
    }
}

void Logo::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float offset(0.f);
    if (!on_)
        offset = 350.f/1024.f;

    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Logo1));

    int mid(window::getViewPort().x_/2);
    int height(0);
    if (window::getViewPort().y_ < settings::iMapYsize)
        height = (window::getViewPort().y_ - settings::iMapYsize)*0.3;
    // const int sx = 400, sy = 350;  // org
    const int sx = 200, sy = 175;  // half
    
    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glTexCoord2f(0, 0 + offset);                   glVertex2f(mid-sx, height);
        glTexCoord2f(0, 0.341796875f + offset);        glVertex2f(mid-sx, height+sy);
        glTexCoord2f(0.78125f, 0.341796875f + offset); glVertex2f(mid+sx, height+sy);
        glTexCoord2f(0.78125f, 0 + offset);            glVertex2f(mid+sx, height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
