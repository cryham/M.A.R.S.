#include "Menu/NewGameConfirm.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "System/window.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"


UiWindow* NewGameConfirm::instance_ = nullptr;
bool NewGameConfirm::kOk_(false);
bool NewGameConfirm::kCancel_(false);


UiWindow* NewGameConfirm::get()
{
    if (settings::bNoConfirmations)
    {
        games::restart();
        return 0;
    }
    if (!instance_)
    {   instance_ = new NewGameConfirm(280, 80);
    
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(180,50), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Cancel), "", &kCancel_,
            Vector2f(80,50), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::QuitCurrentGameText), TEXT_ALIGN_LEFT,
            Vector2f(10,8), 12.f, getColor3f(0.7f, 0.7f, 0.7f), false));
    }
    return instance_;
}

void NewGameConfirm::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
        menus::hideWindow();
        menus::hideWindow();
        games::restart();
    }
    else if (kCancel_)
    {   kCancel_ = false;
        menus::hideWindow();
    }
}

void NewGameConfirm::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
