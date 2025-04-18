#include "Menu/EndMenu.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Menu/ToMainConfirm.hpp"
#include "Games/games.hpp"
#include "Menu/OptionsMenu.hpp"
#include "Menu/InfoHide.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"


UiWindow* EndMenu::instance_ = nullptr;
bool EndMenu::kNew_(false);
bool EndMenu::kOptions_(false);
bool EndMenu::kToMainMenu_(false);
bool EndMenu::kHide_(false);


UiWindow* EndMenu::get()
{
    if (!instance_)
    {   instance_ = new EndMenu(180, 130);
    
        instance_->addWidget(new Button(locales::getLocale(locales::RestartGame),     "", &kNew_,
            Vector2f(10,10), 160, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Options),         "", &kOptions_,
            Vector2f(10,40), 160, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::HideMenu),        "", &kHide_,
            Vector2f(10,70), 160, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::QuitCurrentGame), "", &kToMainMenu_,
            Vector2f(10,100), 160, 20));
    }
    return instance_;
}

void EndMenu::checkWidgets()
{
    if (kToMainMenu_)
    {   kToMainMenu_ = false;

        menus::showWindow(ToMainConfirm::get());
    }
    else if (kOptions_)
    {   kOptions_ = false;

        menus::showWindow(OptionsMenu::get());
    }
    else if (kNew_)
    {   kNew_ = false;

        menus::hideWindow();
        games::restart();
    }
    else if (kHide_)
    {   kHide_ = false;

        if (settings::bShowInfoHide)
            menus::showWindow(InfoHide::get());
        else
            menus::hideMenu();
    }
}

void EndMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
