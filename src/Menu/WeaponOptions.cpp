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

#include "Menu/WeaponOptions.hpp"

#include "Interface/Line.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/LabeledBox.hpp"
#include "Interface/Checkbox.hpp"
#include "Specials/specials.hpp"
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
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_, 
			Vector2f(250,270), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::WeaponOptions), TEXT_ALIGN_LEFT, 
			Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));

        //  weapons
        int x = 20, y = 80, yadd = 20, w = 100;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
        	Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("AFK-47"),      NULL, &kWeapon[weapons::wAFK47],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("WT-FLAMER"),   NULL, &kWeapon[weapons::wBurner],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FIST OF ALI"), NULL, &kWeapon[weapons::wFist],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FLUBBA"),      NULL, &kWeapon[weapons::wFlubba],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("SHOTGUN"),     NULL, &kWeapon[weapons::wShotgun],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("ROCK'n'LOL"),  NULL, &kWeapon[weapons::wRocketLauncher],	Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("ROFLE"),       NULL, &kWeapon[weapons::wROFLE],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("H2-OMG"),      NULL, &kWeapon[weapons::wH2OMG],			Vector2f(x,y), w));  y += yadd;
        //  weapons 2
        x += 150;  y = 80;
        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
            // Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("AFK-85"),      NULL, &kWeapon[weapons::wAFK85],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Flamer2"),     NULL, &kWeapon[weapons::wFlamer2],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Plasma"),      NULL, &kWeapon[weapons::wPlasma],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Shotgun2"),    NULL, &kWeapon[weapons::wShotgun2],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("MiniRockets"), NULL, &kWeapon[weapons::wMiniRockets],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Rifle2"),      NULL, &kWeapon[weapons::wRifle2],			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("H2o-Storm"),   NULL, &kWeapon[weapons::wH2OStorm],		Vector2f(x,y), w));  y += yadd;
        //  weapons 3
        x += 150;  y = 80;
        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons),
            // Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("Pulse"),      NULL, &kWeapon[weapons::wPulse],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Cloud"),      NULL, &kWeapon[weapons::wCloud],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Freezers"),   NULL, &kWeapon[weapons::wFreezers],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Laser"),      NULL, &kWeapon[weapons::wLaser],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Lightning"),  NULL, &kWeapon[weapons::wLightning],	Vector2f(x,y), w));  y += yadd;

        instance_->addWidget(new Checkbox(new sf::String("Minigun"),    NULL, &kWeapon[weapons::wMinigun],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Gauss"),      NULL, &kWeapon[weapons::wGauss],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Grenades"),   NULL, &kWeapon[weapons::wGrenades], 	Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Seekers"),    NULL, &kWeapon[weapons::wSeekers],		Vector2f(x,y), w));  y += yadd;
        //  special
        x += 150;  y = 80;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Specials), 
			Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("FREEZER"),   NULL, &kSpecial[specials::sFreeze],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("HEAL"),      NULL, &kSpecial[specials::sHeal],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("BLAST"),     NULL, &kSpecial[specials::sBlast],		Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FIRE WALL"), NULL, &kSpecial[specials::sFireWall],	Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("SHOCKER"),   NULL, &kSpecial[specials::sShocker],		Vector2f(x,y), w));  y += yadd;
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
