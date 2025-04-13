/* controllers.cpp

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

#include "Controllers/KeyController.hpp"
#include "Controllers/BotController.hpp"
#include "System/settings.hpp"
#include "Players/Player.hpp"

#include <SFML/Window.hpp>

namespace controllers 
{
    namespace
	{
        KeyController* keyControllers1_(NULL);
        KeyController* keyControllers2_(NULL);
        std::vector<BotController*> botControllers_;
    }

    void update()
    {
        if (keyControllers1_ != NULL && (settings::bPlayer1teamL || settings::bPlayer1teamR))
            keyControllers1_->update();
        if (keyControllers2_ != NULL && (settings::bPlayer2teamL || settings::bPlayer2teamR))
            keyControllers2_->update();

        for (auto& it : botControllers_)
            it->update();
    }

    void singleKeyEvent(Key const& keyCode)
    {
        if (keyControllers1_ != NULL && (settings::bPlayer1teamL || settings::bPlayer1teamR))
            keyControllers1_->update(keyCode);
        if (keyControllers2_ != NULL && (settings::bPlayer2teamL || settings::bPlayer2teamR))
            keyControllers2_->update(keyCode);
    }

    void draw()
    {
        for (const auto& it : botControllers_)
            it->draw();
    }

    BotController* addBotController(Player* slave, float strength)
    {
        BotController* bot = new BotController(slave, strength);
        botControllers_.push_back(bot);
        return bot;
    }

    KeyController* addKeyController(Player* slave)
    {
        switch (slave->type())
        {
            case cPlayer1:
                keyControllers1_ = new KeyController(slave);
                return keyControllers1_;
            default:
                keyControllers2_ = new KeyController(slave);
                return keyControllers2_;
        }
    }

    void resetBots()
    {
        for (auto& it : botControllers_)
            it->reset();
    }

    void clear()
    {
        delete keyControllers1_;
        delete keyControllers2_;
        keyControllers1_ = NULL;
        keyControllers2_ = NULL;

        for (auto& it : botControllers_)
            delete it;
        botControllers_.clear();
    }
}
