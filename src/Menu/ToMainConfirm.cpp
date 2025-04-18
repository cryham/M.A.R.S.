#include "Menu/ToMainConfirm.hpp"

#include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Media/music.hpp"
#include "Menu/menus.hpp"
#include "Games/games.hpp"
#include "Locales/locales.hpp"


UiWindow* ToMainConfirm::instance_ = nullptr;
bool ToMainConfirm::kOk_(false);
bool ToMainConfirm::kCancel_(false);


UiWindow* ToMainConfirm::get()
{
    if (settings::bNoConfirmations)
    {
        games::start(games::gMenu);
        music::fadeOut();
        return 0;
    }
    if (!instance_)
    {   instance_ = new ToMainConfirm(280, 80);
    
        instance_->addWidget(new Button(locales::getLocale(locales::Ok),     "", &kOk_,
            Vector2f(180,50), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Cancel), "", &kCancel_,
            Vector2f(80,50), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::QuitCurrentGameText), TEXT_ALIGN_LEFT,
            Vector2f(10,8), 12.f, getColor3f(0.7f, 0.7f, 0.7f), false));
    }
    return instance_;
}

void ToMainConfirm::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        menus::hideWindow();
        menus::hideWindow();
        games::start(games::gMenu);
        music::fadeOut();
    }
    else if (kCancel_)
    {   kCancel_ = false;
        menus::hideWindow();
    }
}

void ToMainConfirm::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
