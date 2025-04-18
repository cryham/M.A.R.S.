#include "Menu/Connect.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Interface/TextBox.hpp"
#include "Interface/Line.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"


UiWindow* Connect::instance_ = nullptr;
bool Connect::kClose_ = false;


UiWindow* Connect::get()
{
    if (!instance_)
    {   instance_ = new Connect(320, 180);

        instance_->addWidget(new Button(locales::getLocale(locales::Close), "", &kClose_,
            Vector2f(220,150), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::StartNetworkGame), TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label("TODO", TEXT_ALIGN_RIGHT,
            Vector2f(310,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(310, 35)));
        instance_->addWidget(new TextBox(locales::getLocale(locales::JoinNetworkText),
            Vector2f(10, 50), 300, 90));
    }
    return instance_;
}

void Connect::checkWidgets()
{
    if (kClose_)
    {   kClose_ = false;
        menus::hideWindow();
    }
}

void Connect::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
