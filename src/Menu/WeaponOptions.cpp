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
#include "System/window.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"
#include "Weapons/weapons.hpp"


UiWindow* WeaponOptions::instance_(NULL);
bool WeaponOptions::kOk_(false);


bool WeaponOptions::kAFK_(false);
bool WeaponOptions::kBurner_(false);
bool WeaponOptions::kFist_(false);
bool WeaponOptions::kFlubba_(false);
bool WeaponOptions::kShotgun_(false);
bool WeaponOptions::kRocket_(false);
bool WeaponOptions::kRofle_(false);
bool WeaponOptions::kH2OMG_(false);

bool WeaponOptions::kAFK2_(false);
bool WeaponOptions::kFlamer2_(false);
bool WeaponOptions::kPlasma_(false);
bool WeaponOptions::kShotgun2_(false);
bool WeaponOptions::kMiniRockets_(false);
bool WeaponOptions::kRifle2_(false);
bool WeaponOptions::kH2OStorm_(false);

bool WeaponOptions::kShocker_(false);
bool WeaponOptions::kFreeze_(false);
bool WeaponOptions::kHeal_(false);
bool WeaponOptions::kBlast_(false);
bool WeaponOptions::kFireWall_(false);


UiWindow* WeaponOptions::get()
{
    if (instance_ == NULL)
    {
        instance_ = new WeaponOptions(3*170+10, 300);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_, 
			Vector2f(250,270), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::WeaponOptions), TEXT_ALIGN_LEFT, 
			Vector2f(10,10), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));

        //  weapons
        int x = 20, y = 80, yadd = 20, w = 100;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons), 
			Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("AFK-47"), NULL, &kAFK_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("WT-FLAMER"), NULL, &kBurner_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FIST OF ALI"), NULL, &kFist_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FLUBBA"), NULL, &kFlubba_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("SHOTGUN"), NULL, &kShotgun_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("ROCK'n'LOL"), NULL, &kRocket_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("ROFLE"), NULL, &kRofle_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("H2-OMG"), NULL, &kH2OMG_, 
			Vector2f(x,y), w));  y += yadd;
        //  weapons2
        x += 150;  y = 80;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Weapons), 
			Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("AFK-85"), NULL, &kAFK2_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Flamer2"), NULL, &kFlamer2_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Plasma"), NULL, &kPlasma_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Shotgun2"), NULL, &kShotgun2_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("MiniRockets"), NULL, &kMiniRockets_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("Rifle2"), NULL, &kRifle2_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("H2o-Storm"), NULL, &kH2OStorm_, 
			Vector2f(x,y), w));  y += yadd;
        //  special
        x += 150;  y = 80;
        instance_->addWidget(new LabeledBox(locales::getLocale(locales::Specials), 
			Vector2f(x-10, y-30), w, 210));
        instance_->addWidget(new Checkbox(new sf::String("FREEZER"), NULL, &kFreeze_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("HEAL"), NULL, &kHeal_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("BLAST"), NULL, &kBlast_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("FIRE WALL"), NULL, &kFireWall_, 
			Vector2f(x,y), w));  y += yadd;
        instance_->addWidget(new Checkbox(new sf::String("SHOCKER"), NULL, &kShocker_, 
			Vector2f(x,y), w));  y += yadd;
    }
    return instance_;
}


void WeaponOptions::onShow()
{
    int en = settings::C_EnabledWeaponsByUser;
    kAFK_      = en & weapons::wAFK47;
    kBurner_   = en & weapons::wBurner;
    kFist_     = en & weapons::wFist;
    kFlubba_   = en & weapons::wFlubba;
    kShotgun_  = en & weapons::wShotgun;
    kRocket_   = en & weapons::wRocketLauncher;
    kRofle_    = en & weapons::wROFLE;
    kH2OMG_    = en & weapons::wH2OMG;

    kAFK2_     = en & weapons::wAFK85;
    kFlamer2_  = en & weapons::wFlamer2;
    kPlasma_   = en & weapons::wPlasma;
    kShotgun2_ = en & weapons::wShotgun2;
    kMiniRockets_ = en & weapons::wMiniRockets;
    kRifle2_   = en & weapons::wRifle2;
    kH2OStorm_ = en & weapons::wH2OStorm;

    kFreeze_   = settings::C_EnabledSpecialsByUser & specials::sFreeze;
    kHeal_     = settings::C_EnabledSpecialsByUser & specials::sHeal;
    kBlast_    = settings::C_EnabledSpecialsByUser & specials::sBlast;
    kFireWall_ = settings::C_EnabledSpecialsByUser & specials::sFireWall;
    kShocker_  = settings::C_EnabledSpecialsByUser & specials::sShocker;
}

void WeaponOptions::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        settings::C_EnabledWeaponsByUser  =
            (kAFK_ ? weapons::wAFK47:0) | (kBurner_ ? weapons::wBurner:0) | (kFist_ ? weapons::wFist:0) |
            (kFlubba_ ? weapons::wFlubba:0) | (kShotgun_ ? weapons::wShotgun:0) |
            (kRocket_ ? weapons::wRocketLauncher:0) | (kRofle_ ? weapons::wROFLE:0) | (kH2OMG_ ? weapons::wH2OMG:0) |
            // new
            (kAFK2_ ? weapons::wAFK85:0) | (kFlamer2_ ? weapons::wFlamer2:0) |
            (kPlasma_ ? weapons::wPlasma:0) | (kShotgun2_ ? weapons::wShotgun2:0) |
            (kMiniRockets_ ? weapons::wMiniRockets:0) | (kRifle2_ ? weapons::wRifle2:0) | (kH2OStorm_ ? weapons::wH2OStorm:0);

        settings::C_EnabledSpecialsByUser =
            (kFreeze_ ? specials::sFreeze:0) | (kHeal_ ? specials::sHeal:0) | (kBlast_ ? specials::sBlast:0) |
            (kFireWall_? specials::sFireWall:0) | (kShocker_? specials::sShocker:0);

        if (settings::C_EnabledWeaponsByUser == 0)
            settings::C_EnabledWeaponsByUser = weapons::wNoWeapon;

        if (settings::C_EnabledSpecialsByUser == 0)
            settings::C_EnabledSpecialsByUser = specials::sNoSpecial;

        menus::hideWindow();
    }
}

void WeaponOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
