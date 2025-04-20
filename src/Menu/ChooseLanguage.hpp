#pragma once

#include "Interface/UiWindow.hpp"

#include <map>


class ChooseLanguage : public UiWindow
{
    public:
        static UiWindow* get();

        void checkWidgets();
        void onShow()
        {   }

        static void reset();

        static void next();
        static void previous();

    private:
        ChooseLanguage(int width, int height): UiWindow(width, height)
        {   }
        ChooseLanguage(ChooseLanguage const& copy);

        static UiWindow* instance_;

        static bool kCancel_;
        static std::map<int, bool*> languageKeyMap_;
        static std::map<sf::String, int> sortedLocales_;
};

