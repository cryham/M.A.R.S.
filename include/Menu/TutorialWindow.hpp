/* TutorialWindow.hpp

Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include "Interface/UiWindow.hpp"
#include "Locales/locales.hpp"


class TutorialWindow: public UiWindow
{
    public:
        static UiWindow* get(locales::LocaleType title, locales::LocaleType text, int index, bool info, bool next);
        static UiWindow* get(sf::String* text, sf::String* title, int index, bool info, bool next);

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
