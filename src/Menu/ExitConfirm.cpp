#include "Menu/ExitConfirm.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "System/window.hpp"
#include "Menu/menus.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"
#include "System/settings.hpp"


UiWindow* ExitConfirm::instance_ = nullptr;
bool ExitConfirm::kOk_(false);
bool ExitConfirm::kCancel_(false);


UiWindow* ExitConfirm::get()
{
    if (settings::bNoConfirmations)
    {
        settings::save();
        window::close();
        return 0;
    }
    if (!instance_)
    {   instance_ = new ExitConfirm(280, 80);
    
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(180,50), 90, 20));
        instance_->addWidget(new Button(locales::getLocale(locales::Cancel), "", &kCancel_,
            Vector2f(80,50), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::QuitText), TEXT_ALIGN_LEFT,
            Vector2f(10,8), 12.f, getColor3f(0.7f, 0.7f, 0.7f), false));
    }
    return instance_;
}

void ExitConfirm::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
        settings::save();
        window::close();
    }
    else if (kCancel_)
    {   kCancel_ = false;
        menus::hideWindow();
    }
}

void ExitConfirm::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
