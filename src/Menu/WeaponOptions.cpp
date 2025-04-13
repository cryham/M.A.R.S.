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

        //  weapons  original
        int x = 20, yTop = 60, y = yTop, yLabel = y-30, yadd = 20, w = 100;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
        	Vector2f(x-10, yLabel), w, 210));
        instance_->addWidget(new Checkbox("AFK-47",      "", &kWeapon[weapons::wAFK47],
            Vector2f(x,y), w, Color3f(0.4, 0.5, 0.9)));  y += yadd;
        instance_->addWidget(new Checkbox("WT-FLAMER",   "", &kWeapon[weapons::wBurner],
            Vector2f(x,y), w, Color3f(0.8, 0.4, 0.1)));  y += yadd;
        instance_->addWidget(new Checkbox("FLUBBA",      "", &kWeapon[weapons::wFlubba],
            Vector2f(x,y), w, Color3f(0.2, 0.8, 0.1)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("FIST OF ALI", "", &kWeapon[weapons::wFist],
            Vector2f(x,y), w, Color3f(0.4, 0.9, 0.6)));  y += yadd;
        instance_->addWidget(new Checkbox("SHOTGUN",     "", &kWeapon[weapons::wShotgun],
            Vector2f(x,y), w, Color3f(0.8, 0.8, 0.3)));  y += yadd;
        instance_->addWidget(new Checkbox("ROCK'n'LOL",  "", &kWeapon[weapons::wRocketLauncher],
            Vector2f(x,y), w, Color3f(0.8, 0.4, 0.2)));  y += yadd;
        instance_->addWidget(new Checkbox("ROFLE",       "", &kWeapon[weapons::wROFLE],
            Vector2f(x,y), w, Color3f(0.8, 0.2, 0.2)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("H2-OMG",      "", &kWeapon[weapons::wH2OMG],
            Vector2f(x,y), w, Color3f(0.4, 0.5, 0.9)));  y += yadd;
        
        //  weapons 2
        x += 150;  y = yTop;
        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
            // Vector2f(x-10, ylab), w, Color3f(0.2, 0.5, 1.0), 210));
        instance_->addWidget(new Checkbox("AFK-85",      "", &kWeapon[weapons::wAFK85],
            Vector2f(x,y), w, Color3f(0.6, 0.6, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("Flamer2",     "", &kWeapon[weapons::wFlamer2],
            Vector2f(x,y), w, Color3f(1.0, 0.7, 0.2)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("Shotgun2",    "", &kWeapon[weapons::wShotgun2],
            Vector2f(x,y), w, Color3f(0.8, 0.5, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("MiniRockets", "", &kWeapon[weapons::wMiniRockets],
            Vector2f(x,y), w, Color3f(0.2, 0.5, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("Rifle2",      "", &kWeapon[weapons::wRifle2],
            Vector2f(x,y), w, Color3f(0.9, 0.2, 0.3)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("H2o-Storm",   "", &kWeapon[weapons::wH2OStorm],
            Vector2f(x,y), w, Color3f(0.4, 0.65, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("Plasma",      "", &kWeapon[weapons::wPlasma],
            Vector2f(x,y), w, Color3f(0.5, 0.9, 0.9)));  y += yadd;
        
        //  weapons 3
        x += 150;  y = yTop;
        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
            // Vector2f(x-10, ylab), w, 210));
        instance_->addWidget(new Checkbox("Pulse",      "", &kWeapon[weapons::wPulse],
            Vector2f(x,y), w, Color3f(1.0, 0.5, 0.8)));  y += yadd;
        instance_->addWidget(new Checkbox("Cloud",      "", &kWeapon[weapons::wCloud],
            Vector2f(x,y), w, Color3f(0.6, 0.6, 1.0)));  y += yadd;
        instance_->addWidget(new Checkbox("Freezers",   "", &kWeapon[weapons::wFreezers],
            Vector2f(x,y), w, Color3f(0.2, 0.7, 0.9)));  y += yadd;
        instance_->addWidget(new Checkbox("Lightning",  "", &kWeapon[weapons::wLightning],
            Vector2f(x,y), w, Color3f(0.6, 0.8, 1.0)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("Laser",      "", &kWeapon[weapons::wLaser],
            Vector2f(x,y), w, Color3f(1.0, 0.5, 0.0)));  y += yadd;
        instance_->addWidget(new Checkbox("Minigun",    "", &kWeapon[weapons::wMinigun],
            Vector2f(x,y), w, Color3f(1.0, 1.0, 0.3)));  y += yadd;
        instance_->addWidget(new Checkbox("Gauss",      "", &kWeapon[weapons::wGauss],
            Vector2f(x,y), w, Color3f(0.8, 0.2, 0.2)));  y += yadd*3/2;

        instance_->addWidget(new Checkbox("Grenades",   "", &kWeapon[weapons::wGrenades],
            Vector2f(x,y), w, Color3f(0.4, 0.5, 0.6)));  y += yadd;
        instance_->addWidget(new Checkbox("Seekers",    "", &kWeapon[weapons::wSeekers],
            Vector2f(x,y), w, Color3f(0.7, 0.8, 0.6)));  y += yadd;
        
        //  specials
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
        kWeapon[i] = settings::C_EnabledWeaponsByUser[i];

    for (int i=0; i < specials::All; ++i)
        kSpecial[i] = settings::C_EnabledSpecialsByUser[i];
}

void WeaponOptions::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        for (int i=0; i < weapons::All; ++i)
            settings::C_EnabledWeaponsByUser[i] = kWeapon[i];

        for (int i=0; i < specials::All; ++i)
            settings::C_EnabledSpecialsByUser[i] = kSpecial[i];

        menus::hideWindow();
    }
}

void WeaponOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
