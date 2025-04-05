/* PauseMenu.cpp

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

#include "Menu/PauseMenu.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Menu/ToMainConfirm.hpp"
#include "Menu/NewGameConfirm.hpp"
#include "Menu/OptionsMenu.hpp"
#include "Menu/MapOptions.hpp"
#include "Menu/InfoHide.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"


UiWindow* PauseMenu::instance_(NULL);
bool PauseMenu::kResume_(false);
bool PauseMenu::kNew_(false);
bool PauseMenu::kOptions_(false);
bool PauseMenu::kMapOptions_(false);
bool PauseMenu::kToMainMenu_(false);
bool PauseMenu::kHide_(false);


UiWindow* PauseMenu::get()
{
    if (instance_ == NULL)
    {
        instance_ = new PauseMenu(180, 170);
        float y = 10, yadd = 30;
        // instance_->addWidget(new Button(locales::getLocale(locales::Continue),     NULL, &kResume_,      Vector2f(10,y), 160, 20));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::RestartGame),     NULL, &kNew_,         Vector2f(10,y), 160, 20));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::Options),         NULL, &kOptions_,     Vector2f(10,y), 160, 20));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::MapOptions),      NULL, &kMapOptions_,  Vector2f(10,y), 160, 20));  y += yadd*3/2;
        instance_->addWidget(new Button(locales::getLocale(locales::HideMenu),        NULL, &kHide_,        Vector2f(10,y), 160, 20));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::QuitCurrentGame), NULL, &kToMainMenu_,  Vector2f(10,y), 160, 20));  y += yadd;
    }
    return instance_;
}

void PauseMenu::checkWidgets()
{
    if (kToMainMenu_)
    {   kToMainMenu_ = false;
        menus::showWindow(ToMainConfirm::get());
    }
    else if (kOptions_)
    {   kOptions_ = false;
        menus::showWindow(OptionsMenu::get());
    }
    else if (kMapOptions_)
    {   kMapOptions_ = false;
        menus::showWindow(MapOptions::get());
    }
    else if (kResume_)
    {   kResume_ = false;
        menus::hideWindow();
    }
    else if (kNew_)
    {   kNew_ = false;
        menus::showWindow(NewGameConfirm::get());
    }
    else if (kHide_)
    {   kHide_ = false;
        if (settings::C_showInfoHide)
            menus::showWindow(InfoHide::get());
        else
            menus::hideMenu();
    }
}

void PauseMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
