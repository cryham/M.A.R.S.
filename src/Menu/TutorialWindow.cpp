#include "Menu/TutorialWindow.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Media/text.hpp"
#include "Interface/TextBox.hpp"
// #include "Interface/Line.hpp"
#include "Locales/locales.hpp"

#include <sstream>


UiWindow* TutorialWindow::instance_ = nullptr;
bool TutorialWindow::kOk_ = false;
sf::String TutorialWindow::index_("1/1");


UiWindow* TutorialWindow::get(locales::LocaleType title, locales::LocaleType text, int index, bool info, bool next)
{
    return get(locales::getLocale(title), locales::getLocale(text), index, info, next);
}

UiWindow* TutorialWindow::get(const sf::String& title, const sf::String& text, int index, bool info, bool next)
{
    reset();
    
    if (!instance_)
    {   instance_ = new TutorialWindow(500, 200);

        instance_->addWidget(new Button(locales::getLocale(next ? locales::Next : locales::Ok), "", &kOk_,
            Vector2f(300,170), 90, 20));
        instance_->addWidget(new Label(title, TEXT_ALIGN_LEFT,
            Vector2f(10,10), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        
        if (info)
            instance_->addWidget(new Label(locales::getLocale(locales::Info), TEXT_ALIGN_RIGHT,
                Vector2f(380,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        else
        {
            std::stringstream sstr;
            sstr << index << "/22";
            index_ = sf::String(sstr.str());
            instance_->addWidget(new Label(index_, TEXT_ALIGN_RIGHT,
                Vector2f(380,18), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        }
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(340, 35)));
        instance_->addWidget(new TextBox(text,
            Vector2f(10,50), 380, 110));
    }
    return instance_;
}

void TutorialWindow::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
        menus::hideWindow();
    }
}

void TutorialWindow::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
