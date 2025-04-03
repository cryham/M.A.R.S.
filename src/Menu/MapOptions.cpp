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
bool MapOptions::kDefaults_(false);
bool MapOptions::kMapSize_[MapOptions::kMapSizes_] = {false,};


UiWindow* MapOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new MapOptions(650, 400);
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_, Vector2f(350,370), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Defaults), NULL, &kDefaults_, Vector2f(210,370), 130, 20));
        int y = 10, yadd = 20;
        instance_->addWidget(new Label(locales::getLocale(locales::MapOptions), TEXT_ALIGN_LEFT, Vector2f(10,y), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));  y += yadd;

        instance_->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects), Vector2f(10, y), 100, 210));  y += yadd*3/2;
        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanets), NULL, &settings::C_MapMinPlanets, 0, 30, 1, Vector2f(20,y), 540, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MaxPlanets), NULL, &settings::C_MapMaxPlanets, 0, 30, 1, Vector2f(20,y), 540, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetsSize), NULL, &settings::C_MapMinPlanetsSize, 1, 300, 1, Vector2f(20,y), 540, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MaxPlanetsSize), NULL, &settings::C_MapMaxPlanetsSize, 1, 300, 1, Vector2f(20,y), 540, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), NULL, &settings::C_MapMinPlanetGap, 0, 300, 1, Vector2f(20,y), 540, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MapHomeRadius), NULL, &settings::C_MapHomeRadius, 1, 300, 1, Vector2f(20,y), 540, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::ShipRadius), NULL, &settings::C_ShipRadius, 5, 50, 10, Vector2f(20,y), 440, 240, true));  y += yadd*3/2;

        //  map Size buttons
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::MapSize), Vector2f(10, y), 100, 210));  y += yadd*3/2;
        for (int i=0; i < MapOptions::kMapSizes_; ++i)
            instance_->addWidget(new Button(locales::getLocale(locales::LocaleType(locales::MapSize0 + i)),
                                            NULL, &kMapSize_[i],  Vector2f(20 + i*90,y), 80, 20));
        y += yadd*3/2;
        //  map Size
        instance_->addWidget(new Slider(locales::getLocale(locales::MapXsize), NULL, &settings::C_MapXsize, 10, 23000, 10, Vector2f(20,y), 620, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MapYsize), NULL, &settings::C_MapYsize, 10, 23000, 10, Vector2f(20,y), 620, 240, true));  y += yadd;
        // C_MapYaspect ..

        y += yadd;
    }
    return instance_;
}

void MapOptions::onShow()
{
}

void MapOptions::checkWidgets()
{
    for (int i=0; i < MapOptions::kMapSizes_; ++i)
        if (MapOptions::kMapSize_[i])
        {   MapOptions::kMapSize_[i] = false;

            switch (i)
            {
            case 0:  settings::C_MapXsize = 600;  break;
            case 1:  settings::C_MapXsize = 900;  break;
            case 2:  settings::C_MapXsize = 1440;  break;  // default
            case 3:  settings::C_MapXsize = 2000;  break;
            case 4:  settings::C_MapXsize = 4000;  break;
            case 5:  settings::C_MapXsize = 6000;  break;
            case 6:  settings::C_MapXsize = 12000;  break;
            }
            float aspY = 910.f / 1440.f;
            // float aspY = 810.f / 1440.f;  // org?
            settings::C_MapYsize = settings::C_MapXsize * aspY;
        }

    if (kDefaults_)
    {   kDefaults_ = false;

        settings::C_MapMinPlanets      = 1;
        settings::C_MapMaxPlanets      = 4;
        settings::C_MapMinPlanetsSize  = 50;
        settings::C_MapMaxPlanetsSize  = 120;

        settings::C_MapMinPlanetGap    = 150;
        settings::C_MapHomeRadius      = 100;

        settings::C_ShipRadius         = 18;
        settings::C_MapXsize           = 1440;
        settings::C_MapYsize           = 810;
        settings::C_MapYaspect         = 1000 * 1440 / 810;
    }

    if (kOk_)
    {   kOk_ = false;

        menus::hideWindow();
    }
}

void MapOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}

