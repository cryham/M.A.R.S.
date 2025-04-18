#include "Media/font.hpp"

#include "System/settings.hpp"
#include "Locales/locales.hpp"

#include <iostream>


namespace font 
{
    namespace
	{
        std::map<int, sf::Font*> fonts_;
    }

    sf::Font* getFont(int languageID)
    {
        auto it = fonts_.find(languageID);
        if (it == fonts_.end())
        {
            // load it from file and...
            sf::Font* font = new sf::Font();
            font->loadFromFile(settings::sDataPath + "fonts/" + locales::getLocales()[languageID].font_);
            fonts_.insert(std::make_pair(languageID, font));
            // ... return it afterwards
            return font;
        }
        else
            return it->second;
    }
}
