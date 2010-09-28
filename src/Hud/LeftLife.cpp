/* LeftLife.cpp

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

# include "Hud/LeftLife.hpp"

# include "Players/players.hpp"
# include "Players/Player.hpp"
# include "System/settings.hpp"
# include "Media/font.hpp"
# include "Media/text.hpp"
# include "System/window.hpp"
# include "Players/Team.hpp"

# include <sstream>

void LeftLife::draw() const {
    text::drawFooText();

    Player const* player(NULL);

    if ((settings::C_playerIteamL && settings::C_playerIIteamL)
         | (settings::C_playerIteamR && settings::C_playerIIteamR)) player = players::getPlayerII();
    else if (settings::C_playerIteamL && settings::C_playerIIteamR) player = players::getPlayerI();
    else if (settings::C_playerIIteamL && settings::C_playerIteamR) player = players::getPlayerII();
    else if (settings::C_playerIteamL)                              player = players::getPlayerI();
    else if (settings::C_playerIIteamL)                             player = players::getPlayerII();

    if (player) {
        Color3f color = player->color();
        if (color.v() < 0.5f) color.v(0.5f);
        Vector2f const& port = window::getViewPort();

        std::stringstream sstr;
        int first(players::getFirstPoints());
        if (player->team()->points() == first) {
            int second(players::getSecondPoints());
            sstr << player->name() << " (" << player->team()->points() << "/ +" << first-second << ")";
        }
        else
            sstr << player->name() << " (" << player->team()->points() << "/ -" << first-player->team()->points() << ")";

        text::drawScreenText(sstr.str(), Vector2f(10, port.y_-85), font::HandelGotDLig, 20.f, TEXT_ALIGN_LEFT, color);

        float life = player->ship()->getLife();
        float fuel = player->ship()->getFuel();

        // player life bar
        glBegin(GL_QUADS);
            Color3f lifeColor(1.f, 0.f, 0.f);
            lifeColor.h(lifeColor.h() + life);
            lifeColor.gl4f(0.9f);
            glVertex2i(16, port.y_-37);
            glVertex2i(16, port.y_-54);
            glVertex2i(16 + life*1.92f, port.y_-54);
            glVertex2i(16 + life*1.92f, port.y_-37);
        glEnd();

        // draw caps
        if (life > 0) {
            if (life == 100.f) {
                glBegin(GL_QUADS);
                    glVertex2i(208, port.y_-54);
                    glVertex2i(214, port.y_-49);
                    glVertex2i(214, port.y_-42);
                    glVertex2i(208, port.y_-37);
                glEnd();
            }

            glBegin(GL_QUADS);
                glVertex2i(16, port.y_-54);
                glVertex2i(10, port.y_-49);
                glVertex2i(10, port.y_-42);
                glVertex2i(16, port.y_-37);
            glEnd();
        }

        // player fuel bar
        glBegin(GL_QUADS);
            glColor4f(1.f,1.f,0.f,0.9f);
            glVertex2i(16, port.y_-10);
            glVertex2i(16, port.y_-27);
            glVertex2i(16 + fuel*1.92f, port.y_-27);
            glVertex2i(16 + fuel*1.92f, port.y_-10);
        glEnd();

        // draw caps
        if (fuel > 0) {
            if (fuel == 100.f) {
                glBegin(GL_QUADS);
                    glVertex2i(208, port.y_-27);
                    glVertex2i(214, port.y_-22);
                    glVertex2i(214, port.y_-15);
                    glVertex2i(208, port.y_-10);
                glEnd();
            }

            glBegin(GL_QUADS);
                glVertex2i(16, port.y_-27);
                glVertex2i(10, port.y_-22);
                glVertex2i(10, port.y_-15);
                glVertex2i(16, port.y_-10);
            glEnd();
        }

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::EnergyBars));
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glTexCoord2i(0, 0); glVertex2f(0, port.y_-64);
            glTexCoord2i(0, 1); glVertex2f(0, port.y_);
            glTexCoord2i(1, 1); glVertex2f(224, port.y_);
            glTexCoord2i(1, 0); glVertex2f(224, port.y_-64);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        /*
        // draw glow
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        // fuel
        glBegin(GL_QUADS);
            glColor4f(1.f,1.f,0.f,0.5f);
            glVertex2i(16, port.y_-10);
            glVertex2i(16, port.y_-27);
            glVertex2i(16 + fuel*1.92f, port.y_-27);
            glVertex2i(16 + fuel*1.92f, port.y_-10);

            glColor4f(1.f,1.f,0.f,0.5f);
            glVertex2i(16, port.y_-27);
            glVertex2i(16 + fuel*1.92f, port.y_-27);
            glColor4f(1.f,1.f,0.f,0.0f);
            glVertex2i(16 + fuel*1.92f, port.y_-37);
            glVertex2i(16, port.y_-37);

            glColor4f(1.f,1.f,0.f,0.5f);
            glVertex2i(16, port.y_-10);
            glVertex2i(16 + fuel*1.92f, port.y_-10);
            glColor4f(1.f,1.f,0.f,0.0f);
            glVertex2i(16 + fuel*1.92f, port.y_);
            glVertex2i(16, port.y_);
        glEnd();
        */
    }
}
