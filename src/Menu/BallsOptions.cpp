#include "Menu/BallsOptions.hpp"

// #include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Slider.hpp"
// #include "Interface/Checkbox.hpp"
// #include "Interface/LabeledBox.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"

#include <SFML/Window.hpp>
#include <sstream>


UiWindow* BallsOptions::instance_ = nullptr;
bool BallsOptions::kOk_(false);
bool BallsOptions::kDefaults_(false);


UiWindow* BallsOptions::get()
{
    if (!instance_)
    {
        instance_ = new BallsOptions(650, 400);
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(350,370), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Defaults), "", &kDefaults_,
            Vector2f(210,370), 130, 20));
        
        int y = 10, yadd = 20, w = 540;
        instance_->addWidget(new Label(locales::getLocale(locales::BallsOptions), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));  y += yadd*2;

        instance_->addWidget(new Slider(locales::getLocale(locales::BallsCount), "",
           &settings::iBallsSB, 1, 200, 1,
           Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::MinPlanetsSize), "",
			&settings::iBallRadiusMin, 5, 50, 1,
			Vector2f(20,y), w, 240, true));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::MaxPlanetsSize), "",
			&settings::iBallRadiusMax, 5, 50, 1,
			Vector2f(20,y), w, 240, true));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::ColorVariation), "",
           &settings::iBallColors, 0, 100, 1,
           Vector2f(20,y), w, 240, true, Slider::None,
            "%1.0f %%", 1.f));  y += yadd;
        instance_->addWidget(new Slider(locales::getLocale(locales::Weight), "",
           &settings::iBallWeight, 0, 300, 1,
           Vector2f(20,y), w, 240, true, Slider::None,
           "%1.0f %%", 1.f));  y += yadd*3/2;

        instance_->addWidget(new Slider(locales::getLocale(locales::RespawnDelay), "",
           &settings::iBallRespawnDelay, -1, 300, 1,
           Vector2f(20,y), w, 240, true, Slider::None,
           "%3.1f s", 10.f));  y += yadd*3/2;
    }
    return instance_;
}

void BallsOptions::checkWidgets()
{
    if (kDefaults_)
    {   kDefaults_ = false;
        
        settings::iBallsSB       = 1;
        settings::iBallRadiusMin = 15;
        settings::iBallRadiusMax = 15;
        settings::iBallColors    = 10;
        settings::iBallWeight    = 100;
        settings::iBallRespawnDelay = -1;
    }
    if (kOk_)
    {   kOk_ = false;

        menus::hideWindow();
    }
}

void BallsOptions::onShow()
{
}

void BallsOptions::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
