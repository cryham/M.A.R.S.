#include "Menu/EndMenu.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/NewGameMenu.hpp"
#include "Menu/menus.hpp"
#include "Menu/ToMainConfirm.hpp"
#include "Games/games.hpp"
#include "Menu/OptionsMenu.hpp"
#include "Menu/InfoHide.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"


UiWindow* EndMenu::instance_ = nullptr;
bool EndMenu::kRestart_(false);
bool EndMenu::kNew_(false);
bool EndMenu::kOptions_(false);
bool EndMenu::kToMainMenu_(false);
bool EndMenu::kHide_(false);


UiWindow* EndMenu::get()
{
    if (!instance_)
    {
        int y = 10, w = 160 * scale_, h = 20, yadd = h + 10;

        instance_ = new EndMenu(w + 20, 180);
        instance_->addWidget(new Button(locales::getLocale(locales::NewGame),         "", &kNew_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::RestartGame),     "", &kRestart_,
            Vector2f(10,y), w, h));  y += yadd*3/2;

        instance_->addWidget(new Button(locales::getLocale(locales::Options),         "", &kOptions_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::HideMenu),        "", &kHide_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::QuitCurrentGame), "", &kToMainMenu_,
            Vector2f(10,y), w, h));  y += yadd;
    }
    return instance_;
}

void EndMenu::checkWidgets()
{
    if (kNew_)
    {   kNew_ = false;

        menus::showWindow(NewGameMenu::get());
        games::restart();
    }
    else if (kRestart_)
    {   kRestart_ = false;

        menus::hideWindow();
        games::restart();
    }
    else if (kOptions_)
    {   kOptions_ = false;

        menus::showWindow(OptionsMenu::get());
    }
    else if (kHide_)
    {   kHide_ = false;

        if (settings::bShowInfoHide)
            menus::showWindow(InfoHide::get());
        else
            menus::hideMenu();
    }
    else if (kToMainMenu_)
    {   kToMainMenu_ = false;

        menus::showWindow(ToMainConfirm::get());
    }
}

void EndMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
