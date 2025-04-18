#include "Menu/InfoDM.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Interface/TextBox.hpp"
#include "Interface/Checkbox.hpp"
#include "Interface/Line.hpp"
#include "Media/text.hpp"
#include "System/settings.hpp"
#include "Locales/locales.hpp"


UiWindow* InfoDM::instance_ = nullptr;
bool InfoDM::kClose_(false);


UiWindow* InfoDM::get()
{
    if (!instance_)
    {
        instance_ = new InfoDM(320*scale_, 300);
        instance_->addWidget(new Button(locales::getLocale(locales::Close), "", &kClose_,
            Vector2f(220,270), 90, 20));
        
        instance_->addWidget(new Label("DeathMatch", TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label(locales::getLocale(locales::Info), TEXT_ALIGN_RIGHT,
            Vector2f(310,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new TextBox(locales::getLocale(locales::ShortDescriptionDM),
            Vector2f(10,40), 300, 30, getColor3f(0.7f, 0.9f, 1.f)));
        instance_->addWidget(new TextBox(locales::getLocale(locales::InfoDM),
            Vector2f(10,80), 300, 160));
        instance_->addWidget(new Checkbox(locales::getLocale(locales::ShowAgainButton), "",
            &settings::bShowInfoDM,
            Vector2f(10,270), 170));
    }
    return instance_;
}

void InfoDM::checkWidgets()
{
    if (kClose_)
    {   kClose_ = false;

        menus::hideWindow();
        settings::save();
    }
}

void InfoDM::onShow()
{
    settings::bShowInfoDM = false;
}

void InfoDM::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
