#include "Menu/GameOptions.hpp"

#include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Slider.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

#include <SFML/Window.hpp>
#include <sstream>


UiWindow* GameOptions::instance_ = nullptr;
bool GameOptions::kOk_(false);
bool GameOptions::kDefaults_(false);


UiWindow* GameOptions::get()
{
    if (!instance_)
    {
        instance_ = new GameOptions(650, 400);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(350,370), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Defaults), "", &kDefaults_,
            Vector2f(180,370), 130, 20));
        
        int y = 10, yadd = 20, w = 540;
        instance_->addWidget(new Label(locales::getLocale(locales::GameOptions), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));  y += yadd*2;

        // instance_->addWidget(new LabeledBox(locales::getLocale(locales::SpaceObjects),
        //    Vector2f(10, y), 100, 210));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::BotsDifficulty, locales::ttBotStrength,
			&settings::iBotsDifficulty, 0, 100, 5,
			Vector2f(20,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd;
        instance_->addWidget(new Slider(locales::PowerUpRate, locales::ttPowerUpRate,
			&settings::iPowerUpRate, 0, 100, 5,
			Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::DamageScale), "",
           &settings::iDamageScale, 0, 200, 1,
           Vector2f(20,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::RespawnDelay), "",
           &settings::iRespawnDelay, 0, 80, 1,
           Vector2f(20,y), w, 240, true, Slider::None,
           "%3.1f s", 10.f));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::Regeneration), "",
           &settings::iRegeneration, 0, 100, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::FuelRegen), "",
           &settings::iFuelRegen, 0, 150, 1,
           Vector2f(20,y), w, 240, true));  y += yadd;
    }
    return instance_;
}

void GameOptions::checkWidgets()
{
    if (kDefaults_)
    {   kDefaults_ = false;
        
        settings::iShipTurnSpeed = 25;  // 25  30 original
        settings::iDamageScale   = 50;  // 50  100 org
        settings::iRegeneration  = 60;  // 60  0 org
        settings::iFuelRegen     = 50;  // 50  0 org
        settings::iRespawnDelay  = 20;  // 20 2 sec  50 org
        settings::iGlowAlpha     = 30;  // 30  100 org
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
    instance_ = nullptr;
}
