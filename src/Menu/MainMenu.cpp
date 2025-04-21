#include "Menu/MainMenu.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Menu/ExitConfirm.hpp"
#include "Menu/OptionsMenu.hpp"
#include "Menu/NewGameMenu.hpp"
#include "Menu/About.hpp"
#include "Menu/InfoSB.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"
#include "Games/games.hpp"


UiWindow* MainMenu::instance_ = nullptr;
bool MainMenu::kNewGame_(false);
bool MainMenu::kStartTut_(false);
bool MainMenu::kOptions_(false);
bool MainMenu::kAbout_(false);
bool MainMenu::kExit_(false);


UiWindow* MainMenu::get()
{
    if (!instance_)
    {
        float y = 10, w = 180 * scale_, h = 20, yadd = h + 10;
        
        instance_ = new MainMenu(w + 20, 190, Vector2f(0.f, 50.f));
        instance_->addWidget(new Button(locales::getLocale(locales::NewGame), "", &kNewGame_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::StartTutorial),  "", &kStartTut_,
            Vector2f(10,y), w, h));  y += yadd*3/2;

        instance_->addWidget(new Button(locales::getLocale(locales::Options),        "", &kOptions_,
            Vector2f(10,y), w, h));  y += yadd*3/2;

        instance_->addWidget(new Button(locales::getLocale(locales::About),          "", &kAbout_,
            Vector2f(10,y), w, h));  y += yadd;
        instance_->addWidget(new Button(locales::getLocale(locales::Quit),           "", &kExit_,
            Vector2f(10,y), w, h));  y += yadd;
    }
    return instance_;
}

void MainMenu::checkWidgets()
{
    if (kExit_)
    {   kExit_ = false;
        menus::showWindow(ExitConfirm::get());
    }
    else if (kAbout_)
    {   kAbout_ = false;
        menus::showWindow(About::get());
    }
    else if (kOptions_)
    {   kOptions_ = false;
        menus::showWindow(OptionsMenu::get());
    }
    else if (kNewGame_)
    {   kNewGame_ = false;
        menus::showWindow(NewGameMenu::get());
        if (settings::bShowInfoSB)
            menus::showWindow(InfoSB::get());
    }
    else if (kStartTut_)
    {   kStartTut_ = false;
        menus::hideWindow();
        games::start(games::gTutorial);
    }
}

void MainMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
