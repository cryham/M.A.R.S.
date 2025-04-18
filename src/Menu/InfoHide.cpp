#include "Menu/InfoHide.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Checkbox.hpp"
#include "Menu/menus.hpp"
#include "Interface/TextBox.hpp"
#include "Interface/Line.hpp"
#include "System/settings.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"


UiWindow* InfoHide::instance_ = nullptr;
bool InfoHide::kOk_(false);


UiWindow* InfoHide::get()
{
    if (!instance_)
    {   instance_ = new InfoHide(320*scale_, 200);

        instance_->addWidget(new Button(locales::getLocale(locales::Close), "", &kOk_,
            Vector2f(220,170), 90, 20));
        
        instance_->addWidget(new Label(locales::getLocale(locales::HideMenu), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label(locales::getLocale(locales::Info), TEXT_ALIGN_RIGHT,
            Vector2f(310,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new TextBox(locales::getLocale(locales::HideMenuText),
            Vector2f(10, 50), 300, 110));
        instance_->addWidget(new Checkbox(locales::getLocale(locales::ShowAgainButton), "",
            &settings::bShowInfoHide,
            Vector2f(10,170), 170));
    }
    return instance_;
}

void InfoHide::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        menus::hideWindow();
        menus::hideMenu();
        settings::save();
    }
}

void InfoHide::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
