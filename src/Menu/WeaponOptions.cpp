/* ShaderError.cpp

Copyright (c) 2025 Crystal Hammer
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

#include "Menu/WeaponOptions.hpp"

#include "Interface/Line.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/LabeledBox.hpp"
#include "Interface/Checkbox.hpp"
#include "Specials/specials.hpp"
#include "System/Color3f.hpp"
#include "System/window.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"
#include "Weapons/weapons.hpp"


UiWindow* WeaponOptions::instance_(NULL);
bool WeaponOptions::kOk_(false);


bool WeaponOptions::kWeapon[weapons::All] = {false,};
bool WeaponOptions::kSpecial[specials::All] = {false,};


UiWindow* WeaponOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new WeaponOptions(4*170+10, 300);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_, 
			Vector2f(250,270), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::WeaponOptions), TEXT_ALIGN_LEFT, 
			Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));

        int x = 20, yTop = 60, y = yTop, yLabel = y-30, yadd = 20, w = 100;

        auto addCheck = [&](const char* text, int wpn, int add = 2)
        {
            instance_->addWidget(new Checkbox(text, "", &kWeapon[wpn],
                Vector2f(x,y), w, weapons::colors[wpn]));  y += yadd * add/2;
        };

        //  weapons  original
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
        	Vector2f(x-10, yLabel), w, 210));

        addCheck("AFK-47",      weapons::wAFK47);
        addCheck("WT-FLAMER",   weapons::wBurner);
        addCheck("FLUBBA",      weapons::wFlubba, 3);

        addCheck("FIST OF ALI",weapons::wFist);
        addCheck("SHOTGUN",    weapons::wShotgun);
        addCheck("ROCK'n'LOL", weapons::wOldRocket);
        addCheck("ROFLE",      weapons::wROFLE, 3);

        addCheck("H2-OMG",     weapons::wH2OMG);
        
        //  weapons 2
        x += 150;  y = yTop;
        addCheck("AFK-85",     weapons::wAFK85);
        addCheck("Flamer2",    weapons::wFlamer2, 3);

        addCheck("Shotgun2",   weapons::wShotgun2);
        addCheck("MiniRockets",weapons::wMiniRockets);
        addCheck("Rifle2",     weapons::wRifle2, 3);

        addCheck("H2o-Storm",  weapons::wH2OStorm);
        addCheck("Plasma",     weapons::wPlasma);
        
        //  weapons 3
        x += 150;  y = yTop;
        addCheck("Pulse",     weapons::wPulse);
        addCheck("Cloud",     weapons::wCloud);
        addCheck("Freezers",  weapons::wFreezers);
        addCheck("Lightning", weapons::wLightning, 3);

        addCheck("Laser",     weapons::wLaser);
        addCheck("Minigun",   weapons::wMinigun);
        addCheck("Gauss",     weapons::wGauss, 3);

        addCheck("Grenades",  weapons::wGrenades);
        addCheck("Seekers",   weapons::wSeekers);
        
        //  specials  ----
        x += 150;  y = yTop;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Specials), 
			Vector2f(x-10, yLabel), w, 210));
        instance_->addWidget(new Checkbox("FREEZER",   "", &kSpecial[specials::sFreeze],
            Vector2f(x,y), w, Color3f(0.3, 1.0, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("HEAL",      "", &kSpecial[specials::sHeal],
            Vector2f(x,y), w, Color3f(0.2, 1.0, 0.0)));  y += yadd;
        instance_->addWidget(new Checkbox("BLAST",     "", &kSpecial[specials::sBlast],
            Vector2f(x,y), w, Color3f(0.9, 0.9, 0.9)));  y += yadd;
        instance_->addWidget(new Checkbox("FIRE WALL", "", &kSpecial[specials::sFireWall],
            Vector2f(x,y), w, Color3f(1.0, 0.6, 0.2)));  y += yadd;
        instance_->addWidget(new Checkbox("SHOCKER",   "", &kSpecial[specials::sShocker],
            Vector2f(x,y), w, Color3f(0.6, 0.8, 1.0)));  y += yadd;
    }
    return instance_;
}


void WeaponOptions::onShow()
{
    for (int i=0; i < weapons::All; ++i)
        kWeapon[i] = settings::bEnabledWeaponsByUser[i];

    for (int i=0; i < specials::All; ++i)
        kSpecial[i] = settings::bEnabledSpecialsByUser[i];
}

void WeaponOptions::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        for (int i=0; i < weapons::All; ++i)
            settings::bEnabledWeaponsByUser[i] = kWeapon[i];

        for (int i=0; i < specials::All; ++i)
            settings::bEnabledSpecialsByUser[i] = kSpecial[i];

        menus::hideWindow();
    }
}

void WeaponOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
