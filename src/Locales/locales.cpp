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

# include "Locales/locales.hpp"

# include "System/settings.hpp"
# include "Media/file.hpp"
# include "Locales/Locale.hpp"

# include <sstream>
# include <iostream>

namespace locales {

    namespace {
        std::vector<Locale>     locales_;
        std::vector<sf::String> localeStrings_(COUNT, "Error");

        bool load(std::string const& fileName) {
            std::vector<sf::String> lines;
            if (file::load(fileName, lines)) {
                for (std::vector<sf::String>::iterator it = lines.begin(); it != lines.end(); ++it) {
                    std::stringstream sstr(it->ToAnsiString());
                    int id;
                    sstr >> id;
                    if (id < COUNT && it->GetSize() > 4) {
                        sf::String tmp(*it);
                        tmp.Erase(0, 4);

                        if (id == ttScreenShotKey)
                            tmp += " " + settings::C_configPath + "screenshots/";
                        localeStrings_[id] = tmp;
                    }
                }
                return true;
            }
            else {
                std::cout << "Failed to open locale " << fileName << "! Interface will be messed up with errors...\n";
                return false;
            }
        }
    }

    bool load() {
        std::cout << "Opening " << settings::C_dataPath << "locales/locales.conf... " << std::flush;
        std::vector<sf::String> lines;
        if (file::load(settings::C_dataPath + "locales/locales.conf", lines)) {
            std::cout << "Done." << std::endl;
            Locale newLocale;
            bool first(true);
            for (std::vector<sf::String>::iterator it = lines.begin(); it != lines.end(); ++it) {
                if ((*it).ToAnsiString()[0] == '[') {
                    if (!first) {
                        locales_.push_back(newLocale);
                        newLocale = Locale();
                    }
                    newLocale.name_ = *it;
                    newLocale.name_.Erase(0, 1);
                    newLocale.name_.Erase(newLocale.name_.GetSize()-1, 1);

                    first = false;
                }
                else {
                    std::stringstream sstr(std::string((*it).ToAnsiString()));
                    std::string flag;
                    sstr >> flag;

                    sf::String arg(*it);
                    arg.Erase(0, flag.size()+1);

                    if (flag == "file:")
                        newLocale.fileName_ = arg;
                    else if (flag == "font:")
                        newLocale.font_ = arg;
                    else if (flag == "author:")
                        newLocale.author_ = "By " + arg;
                    else if (flag == "direction:") {
                        if (arg == "RTL") newLocale.LTR_ = false;
                        else              newLocale.LTR_ = true;
                    }
                    else
                        std::cout << "Unrecognized flag \"" << flag << "\" in " << settings::C_dataPath + "locales/locales.conf !" << std::endl;
                }
            }

            if (!first)
                locales_.push_back(newLocale);

            bool loadSuccess(false);

            load (settings::C_dataPath + "locales/English.txt");
            if (settings::C_languageID < locales_.size()) {
                std::cout << "Loading " << settings::C_dataPath << "locales/" << locales_[settings::C_languageID].fileName_.ToAnsiString() << "... " << std::flush;
                if (load (settings::C_dataPath + "locales/"+locales_[settings::C_languageID].fileName_)) {
                    std::cout << "Done." << std::endl;
                }
                else {
                    std::cout << "Not found! Falling back to English..." << std::endl;
                    settings::C_languageID = 0;
                }

            }
            else {
                std::cout << "Specified language in mars.conf doesn't match any in locales.conf! Falling back to English..." << std::endl;
                settings::C_languageID = 0;
            }

            return true;
        }
        else {
            std::cout << "Not found! Aborting..." << std::endl;
            return false;
        }
    }

    std::vector<Locale>const& getLocales() {
        return locales_;
    }

    sf::String* getLocale(LocaleType type) {
        return &localeStrings_[type];
    }

    Locale const& getCurrentLocale() {
        return locales_[settings::C_languageID];
    }

    void setCurrentLocale() {
        load(settings::C_dataPath + "locales/"+locales_[settings::C_languageID].fileName_);
    }
}


