/* GameOptions.cpp

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

#include "Menu/GameOptions.hpp"

#include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Slider.hpp"
#include "Interface/Checkbox.hpp"
#include "Interface/LabeledBox.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

#include <SFML/Window.hpp>
#include <sstream>


UiWindow* GameOptions::instance_(NULL);
bool GameOptions::kOk_(false);
bool GameOptions::kDefaults_(false);


UiWindow* GameOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new GameOptions(650, 400);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_,
            Vector2f(350,370), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Defaults), NULL, &kDefaults_,
            Vector2f(210,370), 130, 20));
        
        int y = 10, yadd = 20, w = 540;
        instance_->addWidget(new Label(locales::getLocale(locales::GameOptions), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));  y += yadd*2;

        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects),
        //    Vector2f(10, y), 100, 210));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::iDumb, locales::ttBotStrength,
			&settings::C_iDumb, 0, 100, 5,
			Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::PowerUpRate, locales::ttPowerUpRate,
			&settings::C_powerUpRate, 0, 100, 5,
			Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::ShipTurnSpeed), NULL,
           &settings::C_ShipTurnSpeed, 1, 60, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::GlowAlpha), NULL,
           &settings::C_GlowAlpha, 0, 150, 1,
           Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::DamageScale), NULL,
           &settings::C_DamageScale, 0, 200, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::RespawnDelay), NULL,
           &settings::C_RespawnDelay, 0, 80, 1,
           Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::Regeneration), NULL,
           &settings::C_Regeneration, 0, 150, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::FuelRegen), NULL,
           &settings::C_FuelRegen, 0, 150, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
    }
    return instance_;
}

void GameOptions::checkWidgets()
{
    if (kDefaults_)
    {   kDefaults_ = false;
        
        settings::C_ShipTurnSpeed = 25;  // 25  30 original
        settings::C_DamageScale   = 50;  // 50  100 org
        settings::C_Regeneration  = 60;  // 60  0 org
        settings::C_FuelRegen     = 50;  // 50  0 org
        settings::C_RespawnDelay  = 20;  // 20 2 sec  50 org
        settings::C_GlowAlpha     = 30;  // 30  100 org
    }
    if (kOk_)
    {   kOk_ = false;

        // menus::reload();
        menus::hideWindow();
    }
}

void GameOptions::onShow()
{
}

void GameOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
