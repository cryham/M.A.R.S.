#include "Menu/EnterName.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Checkbox.hpp"
#include "Menu/menus.hpp"
#include "Interface/TextEdit.hpp"
#include "Interface/TextBox.hpp"
#include "Interface/Line.hpp"
#include "System/settings.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"


UiWindow* EnterName::instance_ = nullptr;
bool EnterName::kOk_(false);


UiWindow* EnterName::get()
{
    if (!instance_)
    {   instance_ = new EnterName(320, 160);

        instance_->addWidget(new TextEdit("", settings::sPlayer1Name, "PlayerI",
            Vector2f(10,85), 300, 0, TEXT_EDIT, 12));
        instance_->addWidget(new Button(locales::getLocale(locales::Ok), "", &kOk_,
            Vector2f(220,130), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::PleaseEnterName), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label(locales::getLocale(locales::Info), TEXT_ALIGN_RIGHT,
            Vector2f(310,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new TextBox(locales::getLocale(locales::PleaseEnterNameText),
            Vector2f(10,40), 300, 30));
    }
    return instance_;
}

void EnterName::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
    
        menus::hideWindow();
        locales::load();
        menus::reload();
        settings::save();
    }
}

void EnterName::onShow()
{
    settings::bShowInfoHide = false;
}

void EnterName::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
