/* ShaderError.cpp

Copyright (c) 2025 Crystal Hammer

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

#include "Interface/Slider.hpp"
#include "Interface/Tab.hpp"
#include "Interface/TabList.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Checkbox.hpp"
#include "Interface/Label.hpp"
#include "System/settings.hpp"
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
        int w = 620, h = 430;
        instance_ = new MapOptions(w+30, h);
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));

        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(350, h-20), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Defaults), "", &kDefaults_,
            Vector2f(210, h-20), 130, 20));

        instance_->addWidget(new Label(locales::getLocale(locales::MapOptions), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));

        TabList* tabList  = new TabList(Vector2f(10,55), 580, 270);
        Tab* tabSize     = new Tab(locales::getLocale(locales::MapSize), 130);
        Tab* tabObjects  = new Tab(locales::getLocale(locales::SpaceObjects), 130);
        Tab* tabTurrets  = new Tab(locales::getLocale(locales::Turrets), 130);


        int x = 10, y1 = 40, y = y1, yadd = 20;
        // tabObjects->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects),
        //     Vector2f(10, y), 100, 210));  y += yadd;
        tabObjects->addWidget(new Slider(locales::getLocale(locales::MinPlanets), "",
            &settings::iMapMinPlanets, 0, 30, 1,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabObjects->addWidget(new Slider(locales::getLocale(locales::MaxPlanets), "",
            &settings::iMapMaxPlanets, 0, 30, 1,
            Vector2f(x,y), w, 240, true));  y += yadd*3/2;

        tabObjects->addWidget(new Slider(locales::getLocale(locales::MinPlanetsSize), "",
            &settings::iMapMinPlanetsSize, 1, 300, 1,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabObjects->addWidget(new Slider(locales::getLocale(locales::MaxPlanetsSize), "",
            &settings::iMapMaxPlanetsSize, 1, 900, 1,
            Vector2f(x,y), w, 240, true));  y += yadd*3/2;

        tabObjects->addWidget(new Slider(locales::getLocale(locales::MinPlanetGap), "",  // gap
            &settings::iMapMinPlanetGap, 0, 900, 1,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabObjects->addWidget(new Slider(locales::getLocale(locales::MapHomeRadius), "",  // home
            &settings::iMapHomeRadius, 1, 900, 1,
            Vector2f(x,y), w, 240, true));  y += yadd*3/2;

        tabObjects->addWidget(new Slider(locales::getLocale(locales::BlackHoles), "",
            &settings::iMapBlackHoles, -1, 100, 1,
            Vector2f(x,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd;
        tabObjects->addWidget(new Slider(locales::getLocale(locales::Suns), "",  // suns
            &settings::iMapSuns, -1, 100, 1,
            Vector2f(x,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd*3/2;


        //  map Size  buttons  ----
        y = y1;
        // tabSize->addWidget(new LabeledBox(locales::getLocale(locales::MapSize),
        //     Vector2f(10, y), 100, 210));  y += yadd*3/2;
        
        for (int i=0; i < MapOptions::kMapSizes_; ++i)
            tabSize->addWidget(new Button(
                locales::getLocale(locales::LocaleType(locales::MapSize0 + i)), "",
                &kMapSize_[i],  Vector2f(20 + i*90,y), 80, 20));
        y += yadd*3/2;
        
        //  map Size
        tabSize->addWidget(new Slider(locales::getLocale(locales::MapXsize), "",
            &settings::iMapXsize, 10, 23000, 10,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabSize->addWidget(new Slider(locales::getLocale(locales::MapYsize), "",
            &settings::iMapYsize, 10, 23000, 10,
            Vector2f(x,y), w, 240, true));  y += yadd*2;
        // C_MapYaspect..
        
        //  borders []
        tabSize->addWidget(new Label(locales::getLocale(locales::CyclicBorders),
            TEXT_ALIGN_LEFT, Vector2f(20, y)));  //y += yadd;
        tabSize->addWidget(new Checkbox(locales::getLocale(locales::Horizontal), "",
            &settings::bCyclicBorderX,
            Vector2f(w/3.f,y), w/2));  //y += yadd;
        tabSize->addWidget(new Checkbox(locales::getLocale(locales::Vertical), "",
            &settings::bCyclicBorderY,
            Vector2f(2*w/3.f,y), w/3));  y += yadd*2;

        tabSize->addWidget(new Slider(locales::getLocale(locales::GravityScale), "",  // gravity
            &settings::iGravityScale, 5, 300, 10,
            Vector2f(x,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd*3/2;
        tabSize->addWidget(new Slider(locales::getLocale(locales::ShipRadius), "",  // ship
            &settings::iShipRadius, 5, 60, 10,
            Vector2f(x,y), w*2/3.f, 240, true));  y += yadd;
        tabSize->addWidget(new Slider(locales::getLocale(locales::BallRadius), "",  // ball
            &settings::iBallRadius, 5, 60, 10,
            Vector2f(x,y), w*2/3.f, 240, true));  y += yadd*3/2;

        
        //  Turrets  ----
        y = y1;
        tabTurrets->addWidget(new Slider(locales::getLocale(locales::OnHome), "",
            &settings::iTurretsOnHome, 0, 6, 1,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabTurrets->addWidget(new Slider(locales::getLocale(locales::OnPlanets), "",
            &settings::iTurretsOnPlanet, 0, 6, 1,
            Vector2f(x,y), w, 240, true));  y += yadd*3/2;
        
        tabTurrets->addWidget(new Slider(locales::getLocale(locales::AttackSpeed), "",
            &settings::iTurretAttackSpeed, 0, 1000, 1,
            Vector2f(x,y), w, 240, true));  y += yadd;
        tabTurrets->addWidget(new Slider(locales::getLocale(locales::RespawnDelay), "",
            &settings::iTurretRespawnDelay, -1, 600, 1,
            Vector2f(x,y), w, 240, true, Slider::None,
            "%3.1f s", 10.f));  y += yadd;
        tabTurrets->addWidget(new Slider(locales::getLocale(locales::TurnSpeed), "",
            &settings::iTurretTurnSpeed, 1, 100, 10,
            Vector2f(x,y), w, 240, true));  y += yadd;


        tabList->addTab(tabSize);
        tabList->addTab(tabObjects);
        tabList->addTab(tabTurrets);        
        instance_->addWidget(tabList);
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
            case 0:  settings::iMapXsize = 600;   // tiny
                settings::iMapMinPlanets     = 0;    settings::iMapMaxPlanets     = 1;
                settings::iMapMinPlanetsSize = 10;   settings::iMapMaxPlanetsSize = 60;
                settings::iMapMinPlanetGap   = 30;   settings::iMapHomeRadius     = 70;  settings::iShipRadius = 10;
                break;
            case 1:  settings::iMapXsize = 1000;  // small
                settings::iMapMinPlanets     = 0;    settings::iMapMaxPlanets     = 2;
                settings::iMapMinPlanetsSize = 20;   settings::iMapMaxPlanetsSize = 80;
                settings::iMapMinPlanetGap   = 50;   settings::iMapHomeRadius     = 80;  settings::iShipRadius = 14;
                break;
            case 2:  settings::iMapXsize = 1440;  // medium  default
                settings::iMapMinPlanets     = 1;    settings::iMapMaxPlanets     = 4;
                settings::iMapMinPlanetsSize = 50;   settings::iMapMaxPlanetsSize = 120;
                settings::iMapMinPlanetGap   = 150;  settings::iMapHomeRadius     = 100;  settings::iShipRadius = 18;
                break;
            case 3:  settings::iMapXsize = 2000;  // normal
                settings::iMapMinPlanets     = 1;    settings::iMapMaxPlanets     = 5;
                settings::iMapMinPlanetsSize = 60;   settings::iMapMaxPlanetsSize = 120;
                settings::iMapMinPlanetGap   = 150;  settings::iMapHomeRadius     = 150;  settings::iShipRadius = 18;
                break;
            case 4:  settings::iMapXsize = 3000;  // big
                settings::iMapMinPlanets     = 2;    settings::iMapMaxPlanets     = 6;
                settings::iMapMinPlanetsSize = 90;   settings::iMapMaxPlanetsSize = 200;
                settings::iMapMinPlanetGap   = 150;  settings::iMapHomeRadius     = 250;  settings::iShipRadius = 22;
                break;
            case 5:  settings::iMapXsize = 5000;  // large
                settings::iMapMinPlanets     = 3;    settings::iMapMaxPlanets     = 7;
                settings::iMapMinPlanetsSize = 120;  settings::iMapMaxPlanetsSize = 500;
                settings::iMapMinPlanetGap   = 150;  settings::iMapHomeRadius     = 400;  settings::iShipRadius = 30;
                break;
            case 6:  settings::iMapXsize = 9000;  // huge
                settings::iMapMinPlanets     = 4;    settings::iMapMaxPlanets     = 8;
                settings::iMapMinPlanetsSize = 150;  settings::iMapMaxPlanetsSize = 900;
                settings::iMapMinPlanetGap   = 250;  settings::iMapHomeRadius     = 800;  settings::iShipRadius = 50;
                break;
            }
            //- float aspY = settings::iResY / settings::iResX;
            float aspY = 910.f / 1440.f;
            // float aspY = 810.f / 1440.f;  // org?
            settings::iMapYsize = settings::iMapXsize * aspY;
        }

    if (kDefaults_)
    {   kDefaults_ = false;

        settings::iMapMinPlanets     = 1;    settings::iMapMaxPlanets     = 4;
        settings::iMapMinPlanetsSize = 50;   settings::iMapMaxPlanetsSize = 120;
        settings::iMapMinPlanetGap   = 150;  settings::iMapHomeRadius     = 100;  settings::iShipRadius = 18;
        settings::iMapBlackHoles     = -1;   settings::iMapSuns = -1;

        settings::iMapXsize   = 1440;
        settings::iMapYsize   = 810;
        // settings::C_MapYaspect = 1000 * 1440 / 810;
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
