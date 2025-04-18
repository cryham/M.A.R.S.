#include "Hud/RightLife.hpp"

#include "Players/players.hpp"
#include "Players/Player.hpp"
#include "System/settings.hpp"
#include "Media/text.hpp"
#include "System/window.hpp"
#include "Teams/Team.hpp"
#include "Teams/teams.hpp"

#include <sstream>


void RightLife::draw() const
{
    Player const* player = nullptr;

    if (settings::bPlayer1teamL && settings::bPlayer2teamL ||
        settings::bPlayer1teamR && settings::bPlayer2teamR)       player = players::getPlayer1();
    else if (settings::bPlayer1teamL && settings::bPlayer2teamR)  player = players::getPlayer2();
    else if (settings::bPlayer2teamL && settings::bPlayer1teamR)  player = players::getPlayer1();
    else if (settings::bPlayer1teamR)                             player = players::getPlayer1();
    else if (settings::bPlayer2teamR)                             player = players::getPlayer2();

    if (player)
    {
        Color3f color = player->color();
        color.v(1.f);
        color.s(0.3f);
        Vector2f const& port = window::getViewPort();

        std::stringstream sstr;
        int first(teams::getFirstPoints());
        if (player->team()->points() == first)
        {
            int second(teams::getSecondPoints());
            sstr << player->name().toAnsiString() << " (" << player->team()->points() << "/ +" << first-second << ")";
        }
        else
            sstr << player->name().toAnsiString() << " (" << player->team()->points() << "/ -" << first-player->team()->points() << ")";

        text::drawScreenText(sf::String(sstr.str()), Vector2f(port.x_-9.f,port.y_-74.f), 18.f, TEXT_ALIGN_RIGHT, Color3f(0.f, 0.f, 0.f));
        text::drawScreenText(sf::String(sstr.str()), Vector2f(port.x_-10.f,port.y_-75.f), 18.f, TEXT_ALIGN_RIGHT, color);

        float life = player->ship()->getLife();
        float fuel = player->ship()->getFuel();

        // player life bar
        glBegin(GL_QUADS);
            Color3f lifeColor(1.f, 0.f, 0.f);
            lifeColor.h(lifeColor.h() + life);
            lifeColor.gl4f(0.9f);
            glVertex2i(port.x_ - 15, port.y_-32);
            glVertex2i(port.x_ - 15, port.y_-47);
            glVertex2i(port.x_ - 15 - life*1.64f, port.y_-47);
            glVertex2i(port.x_ - 15 - life*1.64f, port.y_-32);
        glEnd();

        // draw caps
        if (life > 0)
        {
            if (life == 100.f)
            {
                glBegin(GL_QUADS);
                    glVertex2i(port.x_ - 179, port.y_-47);
                    glVertex2i(port.x_ - 184, port.y_-43);
                    glVertex2i(port.x_ - 184, port.y_-37);
                    glVertex2i(port.x_ - 179, port.y_-32);
                glEnd();
            }

            glBegin(GL_QUADS);
                glVertex2i(port.x_ - 15, port.y_-47);
                glVertex2i(port.x_ - 10, port.y_-43);
                glVertex2i(port.x_ - 10, port.y_-37);
                glVertex2i(port.x_ - 15, port.y_-32);
            glEnd();
        }

        // player fuel bar
        glBegin(GL_QUADS);
            glColor4f(1.f,1.f,0.f,0.9f);
            glVertex2i(port.x_ - 15, port.y_-8);
            glVertex2i(port.x_ - 15, port.y_-23);
            glVertex2i(port.x_ - 15 - fuel*1.64f, port.y_-23);
            glVertex2i(port.x_ - 15 - fuel*1.64f, port.y_-8);
        glEnd();

        // draw caps
        if (fuel > 0)
        {
            if (fuel == 100.f)
            {
                glBegin(GL_QUADS);
                    glVertex2i(port.x_ - 179, port.y_-23);
                    glVertex2i(port.x_ - 184, port.y_-18);
                    glVertex2i(port.x_ - 184, port.y_-13);
                    glVertex2i(port.x_ - 179, port.y_-8);
                glEnd();
            }

            glBegin(GL_QUADS);
                glVertex2i(port.x_ - 15, port.y_-23);
                glVertex2i(port.x_ - 10, port.y_-18);
                glVertex2i(port.x_ - 10, port.y_-13);
                glVertex2i(port.x_ - 15, port.y_-8);
            glEnd();
        }

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::EnergyBars));
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glTexCoord2f(0, 0); glVertex2f(port.x_, port.y_-64);
            glTexCoord2f(0, 1); glVertex2f(port.x_, port.y_);
            glTexCoord2f(0.75f, 1); glVertex2f(port.x_-192, port.y_);
            glTexCoord2f(0.75f, 0); glVertex2f(port.x_-192, port.y_-64);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
