#pragma once

#include "Interface/UiWindow.hpp"
#include "Locales/locales.hpp"


class TutorialWindow: public UiWindow
{
    public:
        static UiWindow* get(locales::LocaleType title, locales::LocaleType text, int index, bool info, bool next);
        static UiWindow* get(const sf::String& text, const sf::String& title, int index, bool info, bool next);

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

    private:
        TutorialWindow(int width, int height): UiWindow(width, height)
        {   }
        TutorialWindow(TutorialWindow const& copy);

        static UiWindow* instance_;

        static bool kOk_;
        static sf::String index_;
};
