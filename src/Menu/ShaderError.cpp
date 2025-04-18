#include "Menu/ShaderError.hpp"

#include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Locales/locales.hpp"


UiWindow* ShaderError::instance_ = nullptr;
bool ShaderError::kOk_ = false;


UiWindow* ShaderError::get()
{
    if (!instance_)
    {   instance_ = new ShaderError(350, 80);
    
        instance_->addWidget(new Button(locales::getLocale(locales::Ok),     "", &kOk_,
            Vector2f(250,50), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::ShaderError), TEXT_ALIGN_LEFT,
            Vector2f(10,8)));
    }
    return instance_;
}

void ShaderError::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
        menus::hideWindow();
    }
}

void ShaderError::reset()
{
    if (instance_)
        delete instance_;
    instance_ = nullptr;
}
