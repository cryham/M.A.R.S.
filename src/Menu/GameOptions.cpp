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
int  GameOptions::soundVolume_(0);


UiWindow* GameOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new GameOptions(650, 400);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_,
            Vector2f(350,370), 90, 20));
        // instance_->addWidget(new Button(locales::getLocale(locales::Defaults), NULL, &kDefaults_,
        //    Vector2f(210,370), 130, 20));
        int y = 10, yadd = 20;
        instance_->addWidget(new Label(locales::getLocale(locales::GameOptions), TEXT_ALIGN_LEFT,
            Vector2f(10,y), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));  y += yadd;

        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects),
        //    Vector2f(10, y), 100, 210));  y += yadd*3/2;
        // instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanets), NULL,
        //    &settings::C_MapMinPlanets, 0, 30, 1,
        //    Vector2f(20,y), 540, 240, true));  y += yadd;
    }
    return instance_;
}

void GameOptions::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        // menus::reload();

        menus::hideWindow();
    }
    if (soundVolume_ != settings::C_soundVolume)
        settings::C_soundVolume = soundVolume_;
}

void GameOptions::onShow()
{
    soundVolume_ = settings::C_soundVolume;
}

void GameOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
