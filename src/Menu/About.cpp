#include "Menu/About.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Interface/TextBox.hpp"
#include "Interface/TabList.hpp"
#include "System/generateName.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"


UiWindow* About::instance_ = nullptr;
bool About::kClose_ = false;
sf::String About::marsName_("");


UiWindow* About::get()
{
    if (!instance_)
    {
        instance_ = new About(620, 330);
        instance_->addWidget(new Button(locales::getLocale(locales::Close), "", &kClose_,
            Vector2f(320,300), 90, 20));
        instance_->addWidget(new Label("M.A.R.S.", TEXT_ALIGN_LEFT,
            Vector2f(10,0), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label(marsName_, TEXT_ALIGN_RIGHT,
            Vector2f(410,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));

        TabList* tabs = new TabList(Vector2f(10,70), 400, 250);

        Tab* about = new Tab(locales::getLocale(locales::About), 90);
        Tab* license = new Tab(locales::getLocale(locales::License), 90);
        Tab* credits = new Tab(locales::getLocale(locales::Credits), 90);

        about->addWidget(new TextBox(locales::getLocale(locales::AboutText),
            Vector2f(10,30), 390, 200));
        license->addWidget(new TextBox(locales::getLocale(locales::LicenseText),
            Vector2f(10,30), 390, 200));
        credits->addWidget(new Label(locales::getLocale(locales::SpecialThanks), TEXT_ALIGN_LEFT,
            Vector2f(10,30), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        credits->addWidget(new TextBox(locales::getLocale(locales::CreditText),
            Vector2f(10,60), 390, 150));

        tabs->addTab(about);
        tabs->addTab(license);
        tabs->addTab(credits);

        instance_->addWidget(tabs);
    }
    return instance_;
}

void About::checkWidgets()
{
    if (kClose_)
    {   kClose_ = false;
        menus::hideWindow();
    }
}

void About::onShow()
{
    marsName_ = "A " + generateName::game();
}

void About::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
