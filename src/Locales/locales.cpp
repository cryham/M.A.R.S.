/* locales.cpp

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

#include "Locales/locales.hpp"

#include "System/settings.hpp"
#include "System/generateName.hpp"
#include "Media/file.hpp"
#include "Locales/Locale.hpp"

#include <sstream>
#include <iostream>

using namespace std;


namespace locales
{
    namespace
    {
        vector<Locale>     locales_;
        vector<sf::String> localeStrings_(COUNT, "Error");

        bool load(string const& fileName)
        {
            vector<sf::String> lines;
            if (file::load(fileName, lines))
            {
                for (auto& it : lines)
                {
                    stringstream sstr(it.toAnsiString());
                    int id;
                    sstr >> id;
                    if (id < COUNT && it.getSize() > 4)
                    {
                        sf::String tmp(it);
                        tmp.erase(0, 4);

                        for (int i=0; i<tmp.getSize(); ++i)
                        {
                            if (tmp[i] == '{')
                            {
                                int j(i+1);
                                sf::String macro;
                                while (tmp[j] != '}')
                                {
                                    macro.insert(macro.getSize(), tmp[j]);
                                    ++j;
                                    if (j == tmp.getSize())
                                    {
                                        cout << "Error parsing " << fileName << ": At ID " << id <<
                                            " the macro " << macro.toAnsiString() << " misses a trailing '}' !" << endl;
                                        break;
                                    }
                                }
                                tmp.erase(i, j-i+1);

                                if      (macro == "PLAYER1_KEY_UP")      tmp.insert(i, generateName::key(settings::C_playerIup));
                                else if (macro == "PLAYER2_KEY_UP")      tmp.insert(i, generateName::key(settings::C_playerIIup));
                                else if (macro == "PLAYER1_KEY_RIGHT")   tmp.insert(i, generateName::key(settings::C_playerIright));
                                else if (macro == "PLAYER2_KEY_RIGHT")   tmp.insert(i, generateName::key(settings::C_playerIIright));
                                else if (macro == "PLAYER1_KEY_LEFT")    tmp.insert(i, generateName::key(settings::C_playerIleft));
                                else if (macro == "PLAYER2_KEY_LEFT")    tmp.insert(i, generateName::key(settings::C_playerIIleft));
                                else if (macro == "PLAYER1_KEY_FIRE")    tmp.insert(i, generateName::key(settings::C_playerIfire));
                                else if (macro == "PLAYER2_KEY_FIRE")    tmp.insert(i, generateName::key(settings::C_playerIIfire));
                                else if (macro == "PLAYER1_KEY_SPECIAL") tmp.insert(i, generateName::key(settings::C_playerISpecialKey));
                                else if (macro == "PLAYER2_KEY_SPECIAL") tmp.insert(i, generateName::key(settings::C_playerIISpecialKey));
                                else if (macro == "PLAYER1_NAME")        tmp.insert(i, settings::C_playerIName);
                                else if (macro == "PLAYER2_NAME")        tmp.insert(i, settings::C_playerIIName);
                                else if (macro == "DATA_PATH")           tmp.insert(i, settings::C_dataPath);
                                else if (macro == "CONFIG_PATH")         tmp.insert(i, settings::C_configPath);
                                else if (macro == "STATISTICS_KEY")      tmp.insert(i, generateName::key(settings::C_statisticsKey));
                                else
                                    cout << "Error parsing " << fileName << ": At ID " << id <<
                                        " is an unknown macro " << macro.toAnsiString() << "!" << endl;
                            }
                        }

                        //if (id == ttScreenShotKey)
                        //    tmp += " " + settings::C_configPath + "screenshots/";
                        localeStrings_[id] = tmp;
                    }
                }
                return true;
            }
            else
            {
                cout << "Failed to open locale " << fileName << "! Interface will be messed up with errors...\n";
                return false;
            }
        }
    }

    bool load()
    {
        vector<sf::String> lines;
        if (file::load(settings::C_dataPath + "locales/locales.conf", lines))
        {
            locales_.clear();
            Locale newLocale;
            bool first(true);
            for (auto& it : lines)
            {
                if (it.toAnsiString()[0] == '[')
                {
                    if (!first)
                    {
                        locales_.push_back(newLocale);
                        newLocale = Locale();
                    }
                    newLocale.name_ = it;
                    newLocale.name_.erase(0, 1);
                    newLocale.name_.erase(newLocale.name_.getSize()-1, 1);

                    first = false;
                }else
                {
                    stringstream sstr(string(it.toAnsiString()));
                    string flag;
                    sstr >> flag;

                    sf::String arg(it);
                    arg.erase(0, flag.size()+1);

                    if (flag == "file:")
                        newLocale.fileName_ = arg;
                    else if (flag == "font:")
                        newLocale.font_ = arg;
                    else if (flag == "author:")
                        newLocale.author_ = "By " + arg;
                    else if (flag == "direction:")
                    {
                        if (arg == "RTL") newLocale.LTR_ = false;
                        else              newLocale.LTR_ = true;
                    }else
                        cout << "Unrecognized flag \"" << flag << "\" in " << settings::C_dataPath + "locales/locales.conf !" << endl;
                }
            }

            if (!first)
                locales_.push_back(newLocale);

            bool loadSuccess(false);

            load (settings::C_dataPath + "locales/English.txt");
            if (settings::C_languageID < locales_.size())
            {
                if (!load (settings::C_dataPath + "locales/"+locales_[settings::C_languageID].fileName_))
                {
                    cout << "Failed to load " << settings::C_dataPath << "locales/" <<
                        locales_[settings::C_languageID].fileName_.toAnsiString() << "! Falling back to English..." << endl;
                    settings::C_languageID = 0;
                }
            }else
            {
                cout << "Specified language in mars.conf doesn't match any in locales.conf! Falling back to English..." << endl;
                settings::C_languageID = 0;
            }
            return true;
        }
        else
        {
            cout << "Not found! Aborting..." << endl;
            return false;
        }
    }

    vector<Locale>const& getLocales()
    {
        return locales_;
    }

    const sf::String& getLocale(LocaleType type)
    {
        return localeStrings_[type];
    }

    Locale const& getCurrentLocale()
    {
        return locales_[settings::C_languageID];
    }

    void setCurrentLocale()
    {
        load(settings::C_dataPath + "locales/"+locales_[settings::C_languageID].fileName_);
    }
}
