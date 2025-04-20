#include "Menu/PauseMenu.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Menu/ToMainConfirm.hpp"
#include "Menu/NewGameConfirm.hpp"
#include "Menu/OptionsMenu.hpp"
#include "Menu/MapOptions.hpp"
#include "Menu/GameOptions.hpp"
#include "Menu/InfoHide.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"


UiWindow* PauseMenu::instance_ = nullptr;
bool PauseMenu::kResume_(false);
bool PauseMenu::kNew_(false);
bool PauseMenu::kOptions_(false);
bool PauseMenu::kMapOptions_(false);
bool PauseMenu::kGameOptions_(false);
bool PauseMenu::kToMainMenu_(false);
bool PauseMenu::kHide_(false);


UiWindow* PauseMenu::get()
{
    if (!instance_)
    {
        float y = 10, w = 160 * scale_, h = 20, yadd = h + 10;
        
        instance_ = new PauseMenu(w + 20, 210);
        // instance_->addWidget(new Button(locales::getLocale(locales::Continue),     "", &kResume_,
        //  Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::RestartGame),     "", &kNew_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::Options),         "", &kOptions_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::MapOptions),      "", &kMapOptions_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::GameOptions),     "", &kGameOptions_,
            Vector2f(10,y), w, h));  y += yadd*3/2;
        
        instance_->addWidget(new Button(locales::getLocale(locales::HideMenu),        "", &kHide_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::QuitCurrentGame), "", &kToMainMenu_,
            Vector2f(10,y), w, h));  y += yadd;
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
    else if (kGameOptions_)
    {   kGameOptions_ = false;
        menus::showWindow(GameOptions::get());
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
        if (settings::bShowInfoHide)
            menus::showWindow(InfoHide::get());
        else
            menus::hideMenu();
    }
}

void PauseMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
