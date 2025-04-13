/* ChooseLanguage.cpp

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

#include "Menu/ChooseLanguage.hpp"

#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Menu/menus.hpp"
#include "Media/text.hpp"
#include "Locales/locales.hpp"
#include "System/settings.hpp"


UiWindow* ChooseLanguage::instance_(NULL);
bool ChooseLanguage::kCancel_(false);
std::map<int, bool*> ChooseLanguage::languageKeyMap_;
std::map<sf::String, int> ChooseLanguage::sortedLocales_;


UiWindow* ChooseLanguage::get()
{
    if (instance_ == NULL)
    {
        std::vector<Locale>const& localeList = locales::getLocales();

        instance_ = new ChooseLanguage(440, 110 + 12*localeList.size());

        for (int i=0; i < localeList.size(); ++i)
            sortedLocales_.insert(std::make_pair(localeList[i].name_, i));

        int top0 = 50, y = top0, n = 0, x = 10, w = 200;
        for (auto it = sortedLocales_.begin(); it != sortedLocales_.end(); ++it)
        {
            bool* key = new bool(false);
            languageKeyMap_.insert(std::make_pair(it->second, key));

            Button* newButton(new Button(it->first, localeList[it->second].author_, key,
                Vector2f(x, y), w, 20, TEXT_ALIGN_CENTER, font::getFont(it->second)));
            instance_->addWidget(newButton);

            if (it->first == locales::getCurrentLocale().name_)
            {
                instance_->clearFocus();
                newButton->setFocus(newButton, false);
            }
            y += 24;
            ++n;
            if (n > 9)
            {   n = 0;
                y = top0;
                x += w + 20;
            }
        }
        y = top0 + 24 * 10;
        instance_->addWidget(new Button(locales::getLocale(locales::Cancel), "", &kCancel_,
            Vector2f(180, y + 30), 90, 20));
        instance_->addWidget(new Label("Select Language", TEXT_ALIGN_LEFT,
            Vector2f(10, 0),  20.f, getColor3f(0.5f, 0.9f, 1.f), false));
        instance_->addWidget(new Label("* Incomplete", TEXT_ALIGN_LEFT,
            Vector2f(10, y + 10), 12.f, getColor3f(0.5f, 0.9f, 1.f), false));
        // instance_->addWidget(new Line(Vector2f(10, 35), Vector2f(210, 35)));
    }
    return instance_;
}

void ChooseLanguage::checkWidgets()
{
    if (kCancel_)
    {   kCancel_ = false;
        menus::hideWindow();
    }
    for (auto& it : languageKeyMap_)
        if (*(it.second))
        {   *(it.second) = false;

            settings::iLanguageID = it.first;
            locales::load();
            menus::reload();
            settings::save();
            menus::hideWindow();
            break;
        }
}

void ChooseLanguage::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;

    languageKeyMap_.clear();
    for (auto& it : languageKeyMap_)
        delete it.second;
    sortedLocales_.clear();
}

void ChooseLanguage::next()
{
    get();
    for (auto it = sortedLocales_.begin(); it != sortedLocales_.end(); ++it)
    {
        if (it->second == settings::iLanguageID)
        {
            ++it;
            if (it != --sortedLocales_.begin())
            {
                settings::iLanguageID = it->second;
                locales::load();
                menus::reload();
            }
            break;
        }
    }
}

void ChooseLanguage::previous()
{
    get();
    for (auto it = sortedLocales_.begin(); it != sortedLocales_.end(); ++it)
    {
        if (it->second == settings::iLanguageID)
        {
            --it;
            if (it != --sortedLocales_.begin()) 
            {
                settings::iLanguageID = it->second;
                locales::load();
                menus::reload();
            }
            break;
        }
    }
}
