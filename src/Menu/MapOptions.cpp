/* ShaderError.cpp

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

#include "Menu/MapOptions.hpp"

#include "Interface/Line.hpp"
#include "Interface/Slider.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/LabeledBox.hpp"
#include "Interface/Checkbox.hpp"
#include "System/settings.hpp"
#include "System/window.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

UiWindow* MapOptions::instance_(NULL);

bool MapOptions::kOk_(false);

UiWindow* MapOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new MapOptions(550, 300);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_, Vector2f(250,270), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::MapOptions), TEXT_ALIGN_LEFT, Vector2f(10,10), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));

        int y = 30, yadd = 20;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects), Vector2f(10, y), 100, 210));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanets), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanets, 0, 30, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MaxPlanets), locales::getLocale(locales::ttParticleLifetime), &settings::C_MapMaxPlanets, 0, 30, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetsSize), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanetsSize, 1, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MaxPlanetsSize), locales::getLocale(locales::ttParticleLifetime), &settings::C_MapMaxPlanetsSize, 1, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanetGap, 0, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;

        // instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanetGap, 0, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        // instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanetGap, 0, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
        // instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), locales::getLocale(locales::ttParticleCountSlider), &settings::C_MapMinPlanetGap, 0, 300, 1, Vector2f(20,y), 440, 240, true));  y += yadd;
    }
    return instance_;
}

void MapOptions::onShow()
{
    // kFreeze_ = settings::C_MapMinPlanets;
    // kHeal_ = settings::C_MapMaxPlanets;
    // kBlast_ = settings::C_EnabledSpecialsByUser;
    // kFireWall_ = settings::C_EnabledSpecialsByUser;
    // kShocker_ = settings::C_EnabledSpecialsByUser;
}

void MapOptions::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        // if (settings::C_EnabledSpecialsByUser == 0)
        //     settings::C_EnabledSpecialsByUser = specials::sNoSpecial;

        menus::hideWindow();
    }
}

void MapOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}

