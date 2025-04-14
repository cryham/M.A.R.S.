/* settings.cpp

Copyright (c) 2025 Crystal Hammer
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

#include "System/settings.hpp"
#include "Media/file.hpp"
#include "Shaders/postFX.hpp"
#include "Interface/UiElement.hpp"
#include "Specials/specials.hpp"
#include "Weapons/weapons.hpp"
#include "defines.hpp"

#include <string>
#include <sys/stat.h>

#include <fstream>
#include <sstream>
#include <iostream>

#if defined(__WIN32__) || defined(_WIN32)
    #include <shlobj.h>
    #include <windows.h>
#endif

using namespace std;


inline int clamp(int x, int min, int max)
{
    return x < min ? min : (x > max ? max : x);
}

namespace settings
{
    //  game settings  adjustable via options menu
    //----------------------------------------------------------------------------------------------------------------------------------
    int         iSoundVolume =            80;
    int         iAnnouncerVolume =        0;
    int         iMusicVolume =            30;

    bool        bShowFPS =                false;
    bool        bShowParticleCount =      false;
    bool        bFullScreen =             false;
    bool        bVSync =                  true;

    bool        bAdaptiveParticleCount =  false;
    int         iParticleCount =          100;
    int         iParticleLifeTime =       50;
    bool        bStarsHigh =              true;
    int         iStarField =              500;
    //  bots
    int         iBotsLeft =               2;
    int         iBotsRight =              2;
    int         iBotsDeath =              10;
    int         iPointLimitSB =           10;
    int         iPointLimitCK =           10;
    int         iPointLimitDM =           30;
    int         iPointLimitTDM =          50;

    int         iPowerUpRate =            40;
    int         iSlowMoKickIn =           3;
    int         iGameSpeed =              100;

    bool        bShowInfoHide =           true;
    bool        bShowInfoSB =             true;
    bool        bShowInfoDM =             true;
    bool        bShowInfoTDM =            true;
    bool        bShowInfoCK =             true;
    bool        bShowSelectLanguage =     true;
    bool        bShowToolTips =           true;

    bool        bNoConfirmations =        false;
    // int      iUIscale =                150;  // UiElement::scale_
    bool        bLogoSigns =              true;
    int         iCountDown =              3;

    int         iLanguageID =             0;
    //  screen
    int         iResX =                   INITIAL_WINDOW_X;
    int         iResY =                   INITIAL_WINDOW_Y;
    int         iColorDepth =             32;
    int         iAntiAliasing =           0;

    //  post fx
    bool        bShaders =                false;
    bool        bFlashes =                false;
    Key         keyScreenShot =           Key(sf::Keyboard::F12);
    //  audio
    bool        bAudioRandom =            true;
    Key         keyAudioNext =            Key(sf::Keyboard::F8);
    Key         keyAudioPrev =            Key(sf::Keyboard::F7);
    Key         keyStatistics =           Key(sf::Keyboard::Tab);

    string      sConfigPath =             "";
    string      sDataPath =               "";
    string      sScreenShotFormat =       "jpg";

    //  map setup
    int         iMapMinPlanets      = 1;
    int         iMapMaxPlanets      = 4;
    int         iMapMinPlanetsSize  = 50;
    int         iMapMaxPlanetsSize  = 120;

    int         iMapBlackHoles      = -1;  // -1 map default
    int         iMapSuns            = -1;

    int         iMapMinPlanetGap    = 150;
    int         iMapHomeRadius      = 100;

    int         iShipRadius         = 18;
    int         iMapXsize           = 1440;
    int         iMapYsize           = 810;
    // int      iMapYaspect         = 1000 * 1440 / 810;  // / 1000 = 1
    int         iBallRadius         = 15;

    int         iShipTurnSpeed   = 25;
    int         iDamageScale     = 70;
    int         iRegeneration    = 60;
    int         iFuelRegen       = 150;
    int         iRespawnDelay    = 20;
    int         iGlowAlpha       = 30;

    bool        bCyclicBorderX   = false;
    bool        bCyclicBorderY   = false;
    int         iGravityScale    = 100;

    //  weapons
    bool        bEnabledWeapons[weapons::All] = {true,};
    bool        bEnabledWeaponsByUser[weapons::All] = {true,};
    bool        bEnabledSpecials[specials::All] =  {true,};
    bool        bEnabledSpecialsByUser[specials::All] = {true,};


    //  player settings -----
    sf::String    sPlayer1Name =      "PlayerI";
    Color3f       clr1Player =        Color3f(1.f, 0.87f, 0.0125f);
    Color3f       clr1Team =          Color3f(0.94f, 0.24f, 1.f);
    
    Key           key1up =            Key(sf::Keyboard::Up);
    Key           key1down =          Key(sf::Keyboard::Down);
    Key           key1boost =         Key(sf::Keyboard::RAlt);

    Key           key1left =          Key(sf::Keyboard::Left);
    Key           key1right =         Key(sf::Keyboard::Right);
    Key           key1fire =          Key(sf::Keyboard::RShift);

    Key           key1SpecialKey =    Key(sf::Keyboard::RControl);
    Key           key1prev =          Key(sf::Keyboard::PageUp);
    Key           key1next =          Key(sf::Keyboard::PageDown);

    bool          bPlayer1teamL =     false;
    bool          bPlayer1teamR =     true;
    int           iPlayer1Ship =      4;
    bool          bPlayer1mouseAim =  true;

    weapons::WeaponType   player1Weapon =  weapons::wAFK47;
    specials::SpecialType player1Special = specials::sHeal;
    
    sf::String    sPlayer2Name =      "PlayerII";
    Color3f       clr2Player =        Color3f(0.5f, 0.4f, 0.82f);
    Color3f       clr2Team =          Color3f(0.05f, 1.f, 0.785f);

    Key           key2up =            Key(sf::Keyboard::W);
    Key           key2down =          Key(sf::Keyboard::S);
    Key           key2boost =         Key(sf::Keyboard::LAlt);

    Key           key2left =          Key(sf::Keyboard::A);
    Key           key2right =         Key(sf::Keyboard::D);
    Key           key2fire =          Key(sf::Keyboard::LShift);

    Key           key2SpecialKey =    Key(sf::Keyboard::LControl);
    Key           key2prev =          Key(sf::Keyboard::Num1);
    Key           key2next =          Key(sf::Keyboard::Num2);

    bool          bPlayer2teamL =     true;
    bool          bPlayer2teamR =     false;
    int           iPlayer2Ship =      1;
    bool          bPlayer2mouseAim =  false;

    weapons::WeaponType   player2Weapon =  weapons::wAFK47;
    specials::SpecialType player2Special = specials::sHeal;


    //  ai settings ------
    bool        bDrawBotJobs =             false;
    bool        bDrawZones =               false;
    bool        bDrawAIPath =              false;
    int         iBotsDifficulty =          30;

    //  network settings ----- unused
    // sf::String sIP =                      "192.168.0.1";
    // sf::String sPort =                    "12345";
    // bool          bNetworkPlayerI =        true;
    // bool          showLatency =           false;


    //  utility
    //----------------------------------------------------------------------------------------------------------------------------------

    //  bool
    void readBool(istringstream& iss, string inputLine, bool& val)
    {
        string s;  iss >> s;
        if (s == "on")   val = true;
        else
        if (s == "off")  val = false;
        else
            cout << s << " is a bad value for " << inputLine << ". Use on or off instead.\n";
    }

    string strBool(bool val)
    {
        return val ? "on" : "off";
    }

    //  int
    void readInt(istringstream& iss, int& val, int intMin, int intMax)
    {
        int value;
        iss >> value;
        val = clamp(value, intMin, intMax);
    }

    void readInt(istringstream& iss, int& val)
    {
        int value;
        iss >> value;
        val = value;
    }

    //  string
    void readString(istringstream& iss, sf::String& val, int len)
    {
        sf::String tmp;
        sf::Uint32 character(0);
        iss >> character;
        int i = 0;
        while (character != 0 && i++ < len)
        {
            tmp.insert(tmp.getSize(), character);
            iss >> character;
        }
        val = tmp;
    }

    void strMax(ofstream& outStream, const sf::String& str, int maxLen)
    {
        int i = 0;
        while (i < maxLen && i < str.getSize())
        {
            outStream << str[i] << " ";
            ++i;
        }
        outStream << "0" << endl;
    }

    //  color
    void readColor(istringstream& iss, Color3f& clr)
    {
        float r,g,b;
        iss >> r >> g >> b;
        clr = Color3f(r,g,b);
    }

    void strColor(ofstream& outStream, const Color3f& clr)
    {
        outStream <<  clr.r() << " "<< clr.g() << " " << clr.b() << endl;
    }


    //  SAVE
    //----------------------------------------------------------------------------------------------------------------------------------
    bool save()
    {
        ofstream oss((sConfigPath + "mars.cfg").c_str());
        if (oss)
        {
            oss << "// mars config file" << endl;
            oss << "// nearly all these options can be changed with the in-game menu, too." << endl << endl;

            //  ----
            oss << "soundVolume "           << iSoundVolume << endl;
            oss << "announcerVolume "       << iAnnouncerVolume << endl;
            oss << "musicVolume "           << iMusicVolume << endl << endl;

            oss << "iParticleCount "   << iParticleCount << endl;
            oss << "iParticleLifeTime "<< iParticleLifeTime << endl << endl;
            
            oss << "showFPS "               << strBool(bShowFPS) << endl;
            oss << "showParticleCount "     << strBool(bShowParticleCount) << endl;
            // oss << "showLatency "           << strBool(showLatency) << endl << endl;

            oss << "fullScreen "            << strBool(bFullScreen) << endl;
            oss << "vsync "                 << strBool(bVSync) << endl << endl;
            
            oss << "drawAIPath "            << strBool(bDrawAIPath) << endl;
            oss << "BotsDifficulty "        << iBotsDifficulty << endl;
            oss << "adaptiveParticleCount " << strBool(bAdaptiveParticleCount) << endl;
            oss << "drawBotJobs "           << strBool(bDrawBotJobs) << endl;
            oss << "drawZones "             << strBool(bDrawZones) << endl << endl;
            //  points
            oss << "botsLeft "              << iBotsLeft << endl;
            oss << "botsRight "             << iBotsRight << endl;
            oss << "botsDeath "             << iBotsDeath << endl;
            oss << "pointLimitSB "          << iPointLimitSB << endl;
            oss << "pointLimitCK "          << iPointLimitCK << endl;
            oss << "pointLimitDM "          << iPointLimitDM << endl;
            oss << "pointLimitTDM "         << iPointLimitTDM << endl << endl;
            
            oss << "powerUpRate "           << iPowerUpRate << endl;
            oss << "slowMoKickIn "          << iSlowMoKickIn << endl;
            oss << "gameSpeed "             << iGameSpeed << endl << endl;

            //----  player I
            oss << "playerIName ";          strMax(oss, sPlayer1Name, 12);
            oss << "playerIKeys "           <<  key1up << " " << key1right << " " << key1left << " "
                << key1fire << " " << key1SpecialKey << " "
                << key1down << " " << key1boost << " " << key1prev << " " << key1next << endl;
            
            oss << "playerIColor ";         strColor(oss, clr1Player);
            oss << "playerITeamColor ";     strColor(oss, clr1Team);
            oss << "playerITeamL "          << strBool(bPlayer1teamL) << endl;
            oss << "playerITeamR "          << strBool(bPlayer1teamR) << endl;
            
            oss << "playerIShip "           <<  iPlayer1Ship << endl;
            oss << "playerIWeapon "         <<  player1Weapon << endl;
            oss << "playerISpecial "        <<  player1Special << endl;
            oss << "playerImouseAim "       << strBool(bPlayer1mouseAim) << endl << endl;
            //----  player II
            oss << "playerIIName ";         strMax(oss, sPlayer2Name, 12);
            oss << "playerIIKeys "          <<  key2up << " "<< key2right << " " << key2left << " "
                << key2fire << " " << key2SpecialKey << " "
                << key2down << " " << key2boost << " " << key2prev << " " << key2next << endl;

            oss << "playerIIColor ";        strColor(oss, clr2Player);
            oss << "playerIITeamColor ";    strColor(oss, clr2Team);
            oss << "playerIITeamL "         << strBool(bPlayer2teamL) << endl;
            oss << "playerIITeamR "         << strBool(bPlayer2teamR) << endl;
            
            oss << "playerIIShip "          <<  iPlayer2Ship << endl;
            oss << "playerIIWeapon "        <<  player2Weapon << endl;
            oss << "playerIISpecial "       <<  player2Special << endl;
            oss << "playerIImouseAim "      << strBool(bPlayer2mouseAim) << endl << endl;
            
            //  net unused
            // oss << "connectIP "             << sIP.toAnsiString() << endl;
            // oss << "connectPort "           << sPort.toAnsiString() << endl;
            // oss << "networkTeamRed "        << strBool(bNetworkPlayerI) << endl << endl;
            //  show
            oss << "showInfoHide "          << strBool(bShowInfoHide) << endl;
            oss << "showInfoSB "            << strBool(bShowInfoSB) << endl;
            oss << "showInfoDM "            << strBool(bShowInfoDM) << endl;
            oss << "showInfoTDM "           << strBool(bShowInfoTDM) << endl;
            oss << "showInfoCK "            << strBool(bShowInfoCK) << endl << endl;

            //  UI  ----
            oss << "languageID "            << iLanguageID << endl;
            oss << "showSelectLanguage "    << strBool(bShowSelectLanguage) << endl << endl;
            oss << "showToolTips "          << strBool(bShowToolTips) << endl;
            //  UI new
            oss << "NoConfirmations "       << strBool(bNoConfirmations) << endl;
            oss << "UIScale "               << UiElement::scale_ << endl;
            oss << "LogoSigns "             << strBool(bLogoSigns) << endl;
            oss << "CountDown "             << iCountDown << endl << endl;

            oss << "highStarResolution "    << strBool(bStarsHigh) << endl;
            oss << "starField "             << iStarField << endl << endl;
            
            //  post fx  ----
            oss << "shaders "               << strBool(bShaders) << endl;
            oss << "postFXflashes "         << strBool(bFlashes) << endl << endl;
            //  screen
            oss << "resolutionX "           << iResX << endl;
            oss << "resolutionY "           << iResY << endl;
            oss << "colorDepth "            << iColorDepth << endl;
            oss << "antiAliasing "          << iAntiAliasing << endl << endl;
            //  keys
            oss << "screenShotKey "         << keyScreenShot << endl;
            oss << "statisticsKey "         << keyStatistics << endl;
            oss << "screenShotFormat "      << sScreenShotFormat << endl << endl;
            
            //  audio  ----
            oss << "audioRandom "           << strBool(bAudioRandom) << endl;
            oss << "audioNextKey "          << keyAudioNext << endl;
            oss << "audioPreviousKey "      << keyAudioPrev << endl << endl;
            //  weapons
            for (int i=0; i < weapons::All; ++i)
                oss << "enabledWeapons"<< i <<" "  << strBool(bEnabledWeaponsByUser[i]) << endl;
            oss << endl;
            for (int i=0; i < specials::All; ++i)
                oss << "enabledSpecials"<< i <<" " << strBool(bEnabledSpecialsByUser[i]) << endl;
            oss << endl;
            //  map  ----
            oss << "MapXsize "              << iMapXsize << endl;
            oss << "MapYsize "              << iMapYsize << endl;
            oss << "MapMinPlanets "         << iMapMinPlanets << endl;
            oss << "MapMaxPlanets "         << iMapMaxPlanets << endl;
            oss << "MapMinPlanetsSize "     << iMapMinPlanetsSize << endl;
            oss << "MapMaxPlanetsSize "     << iMapMaxPlanetsSize << endl;
            oss << "MapMinPlanetGap "       << iMapMinPlanetGap << endl << endl;

            oss << "MapBlackHoles "         << iMapBlackHoles << endl;
            oss << "MapSuns "               << iMapSuns << endl << endl;

            oss << "MapHomeRadius "         << iMapHomeRadius << endl;
            oss << "ShipRadius "            << iShipRadius << endl;
            oss << "BallRadius "            << iBallRadius << endl << endl;

            oss << "CyclicBorderX "         << strBool(bCyclicBorderX) << endl;
            oss << "CyclicBorderY "         << strBool(bCyclicBorderY) << endl;
            oss << "GravityScale "          << iGravityScale << endl << endl;
            //  game
            oss << "ShipTurnSpeed "         << iShipTurnSpeed << endl;
            oss << "DamageScale "           << iDamageScale << endl;
            oss << "Regeneration "          << iRegeneration << endl;
            oss << "FuelRegen "             << iFuelRegen << endl << endl;
            oss << "RespawnDelay "          << iRespawnDelay << endl;
            oss << "GlowAlpha "             << iGlowAlpha << endl;

            oss.close();
            return true;
        }else
        {   cout << "Faild to save configuration file " << sConfigPath << "mars.cfg!" << endl;
            return false;
        }
    }

    //  LOAD
    //----------------------------------------------------------------------------------------------------------------------------------
    bool load()
    {
        // check whether application directory in the home diretory exists, if not create it
        #ifdef __linux__
            string home(getenv("HOME"));
            if (*home.rbegin() != '/') home += '/';
            mkdir((home + ".marsshooter/").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif

        #if defined(__WIN32__) || defined(_WIN32)
            TCHAR szAppData[MAX_PATH];
            SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
            string home(szAppData);
            CreateDirectory((home + "/.marsshooter/").c_str(), NULL);
        #endif

        #ifdef __APPLE__
            string home(getenv("HOME"));
            if (*home.rbegin() != '/') home += '/';
            mkdir((home + "Library/Preferences/mars/").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif

        // search for config file
        if (sConfigPath == "")
        {
            bool success(false);
            cout << "Searching for configuration file... " << flush;
            sConfigPath = "./";

            #ifdef __linux__
                string home(getenv("HOME"));
                if (*home.rbegin() != '/') home += '/';

                if (ifstream((sConfigPath + "mars.cfg").c_str()))
                    success = true;
                else if (ifstream((home + ".marsshooter/mars.cfg").c_str()))
                {
                    sConfigPath =      home + ".marsshooter/";
                    success = true;
                }else
                    sConfigPath =      home + ".marsshooter/";
            #endif

            #if defined(__WIN32__) || defined(_WIN32)
                TCHAR szAppData[MAX_PATH];
                SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
                string home(szAppData);

                if (ifstream((C_configPath + "mars.cfg").c_str()))
                    success = true;
                else if (ifstream((home + "/.marsshooter/mars.cfg").c_str()))
                {
                    C_configPath =      home + "/.marsshooter/";
                    success = true;
                }else
                    C_configPath =      home + "/.marsshooter/";
            #endif

            #ifdef __APPLE__
                string home(getenv("HOME"));
                if (*home.rbegin() != '/') home += '/';

                if (ifstream((home + "Library/Preferences/mars/mars.cfg").c_str()))
                {
                    C_configPath =      home + "Library/Preferences/mars/";
                    success = true;
                }else
                    C_configPath =      home + "Library/Preferences/mars/";
            #endif

            if (success) cout << "Found " << sConfigPath << "mars.cfg"  << endl;
            else         cout << "Found nothing. Will create a new one." << endl;
        }

        // search for data files
        if (sDataPath == "")
        {
            bool success(false);
            cout << "Searching for data files... " << flush;
            sDataPath = "./data/";

            #ifdef __linux__
                if (ifstream((sDataPath + "locales/English.txt").c_str()))
                    success = true;
                else if (ifstream("/usr/share/marsshooter/locales/English.txt"))
                {   sDataPath = "/usr/share/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/share/games/marsshooter/locales/English.txt"))
                {   sDataPath = "/usr/share/games/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/share/games/marsshooter/locales/English.txt"))
                {   sDataPath = "/usr/local/share/games/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/share/marsshooter/locales/English.txt"))
                {   sDataPath = "/usr/local/share/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/games/marsshooter/locales/English.txt"))
                {   sDataPath = "/usr/local/games/marsshooter/";
                    success = true;
                }
            #endif

            #if defined(__WIN32__) || defined(_WIN32)
                if (ifstream((C_dataPath + "locales/English.txt").c_str()))
                    success = true;
            #endif

            #ifdef __APPLE__
                if (ifstream("../Resources/data/locales/English.txt"))
                {   C_dataPath = "../Resources/data/";
                    success = true;
                }
            #endif

            if (success)
                cout << "Found " << sDataPath << endl;
            else
            {   cout << "Found nothing. Aborting." << endl;
                return false;
            }
        }

        //  read lines
        //----------------------------------------------------------------------------------------------------------------------------------
        //  weapons
        for (int i=0; i < weapons::All; ++i)
        {
            bEnabledWeaponsByUser[i] = bEnabledWeapons[i] = true;
        }
        for (int i=0; i < specials::All; ++i)
        {
            bEnabledSpecialsByUser[i] = bEnabledSpecials[i] = true;
        }

        vector<sf::String> lines;
        if (file::load(sConfigPath + "mars.cfg", lines))
        {
            // clear();  //..
            for (auto& it : lines)
            {
                istringstream iss (it.toAnsiString());
                string line;
                iss >> line;

                bool found = false;
                for (int i=0; i < weapons::All; ++i)
                {
                    stringstream ss;
                    ss << "enabledWeapons" << i << "]";
                    if (line == ss.str())
                    {
                        readBool(iss, line, bEnabledWeaponsByUser[i]);   bEnabledWeapons[i] = bEnabledWeaponsByUser[i];
                        found = true;
                    }
                }
                if (found)  continue;
                for (int i=0; i < specials::All; ++i)
                {
                    stringstream ss;
                    ss << "enabledSpecials" << i << "]";
                    if (line == ss.str())
                    {
                        readBool(iss, line, bEnabledSpecialsByUser[i]);   bEnabledSpecials[i] = bEnabledSpecialsByUser[i];
                        found = true;
                    }
                }
                if (found)  continue;

                if      (line == "soundVolume")            readInt(iss, iSoundVolume, 0, 100);
                else if (line == "announcerVolume")        readInt(iss, iAnnouncerVolume, 0, 100);
                else if (line == "musicVolume")            readInt(iss, iMusicVolume, 0, 100);
                
                else if (line == "iParticleCount")         readInt(iss, iParticleCount, 10, 300);
                else if (line == "iParticleLifeTime")      readInt(iss, iParticleLifeTime, 10, 300);
                
                else if (line == "showFPS")                readBool(iss, line, bShowFPS);
                else if (line == "showParticleCount")      readBool(iss, line, bShowParticleCount);
                // else if (line == "showLatency")         readBool(iss, line, showLatency);
                
                else if (line == "fullScreen")             readBool(iss, line, bFullScreen);
                else if (line == "vsync")                  readBool(iss, line, bVSync);
                
                else if (line == "drawAIPath")             readBool(iss, line, bDrawAIPath);
                else if (line == "BotsDifficulty")         readInt(iss, iBotsDifficulty, 0, 100);

                else if (line == "adaptiveParticleCount")  readBool(iss, line, bAdaptiveParticleCount);
                else if (line == "drawBotJobs")            readBool(iss, line, bDrawBotJobs);
                else if (line == "drawZones")              readBool(iss, line, bDrawZones);
                //  points
                else if (line == "botsLeft")               readInt(iss, iBotsLeft, 0, 20);
                else if (line == "botsRight")              readInt(iss, iBotsRight, 0, 20);
                else if (line == "botsDeath")              readInt(iss, iBotsDeath, 0, 80);
                else if (line == "pointLimitSB")           readInt(iss, iPointLimitSB, 1, 100);
                else if (line == "pointLimitCK")           readInt(iss, iPointLimitCK, 1, 100);
                else if (line == "pointLimitDM")           readInt(iss, iPointLimitDM, 1, 400);
                else if (line == "pointLimitTDM")          readInt(iss, iPointLimitTDM,1, 400);

                else if (line == "powerUpRate")            readInt(iss, iPowerUpRate, 0, 100);
                else if (line == "slowMoKickIn")           readInt(iss, iSlowMoKickIn, 0, 100);
                else if (line == "gameSpeed")              readInt(iss, iGameSpeed, 50, 200);
                //----  players
                else if (line == "playerIName")            readString(iss, sPlayer1Name, 12);
                else if (line == "playerIIName")           readString(iss, sPlayer2Name, 12);
                else if (line == "playerIKeys") {
                    iss >> key1up >> key1right >> key1left >> key1fire >> key1SpecialKey;
                    iss >> key1down >> key1boost >> key1prev >> key1next;
                }
                else if (line == "playerIIKeys") {
                    iss >> key2up >> key2right >> key2left >> key2fire >> key2SpecialKey;
                    iss >> key2down >> key2boost >> key2prev >> key2next;
                }
                else if (line == "playerIColor")       readColor(iss, clr1Player);
                else if (line == "playerIIColor")      readColor(iss, clr2Player);
                else if (line == "playerITeamColor")   readColor(iss, clr1Team);
                else if (line == "playerIITeamColor")  readColor(iss, clr2Team);
                
                else if (line == "playerITeamL")       readBool(iss, line, bPlayer1teamL);
                else if (line == "playerITeamR")       readBool(iss, line, bPlayer1teamR);
                else if (line == "playerIShip")        iss >> iPlayer1Ship;
                else if (line == "playerIIShip")       iss >> iPlayer2Ship;

                else if (line == "playerIWeapon") {    int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    player1Weapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (line == "playerISpecial") {   int tmp;  iss >> tmp;
                    player1Special = static_cast<specials::SpecialType>(tmp);
                }
                else if (line == "playerIIWeapon") {   int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    player2Weapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (line == "playerIISpecial") {  int tmp;  iss >> tmp;
                    player2Special = static_cast<specials::SpecialType>(tmp);
                }
                else if (line == "playerImouseAim")     readBool(iss, line, bPlayer1mouseAim);
                else if (line == "playerIImouseAim")    readBool(iss, line, bPlayer2mouseAim);

                else if (line == "playerIITeamL")       readBool(iss, line, bPlayer2teamL);
                else if (line == "playerIITeamR")       readBool(iss, line, bPlayer2teamR);
                //----
                //  net unused
                // else if (line == "connectIP") {         string tmp;  iss >> tmp;  sIP = sf::String(tmp);    }
                // else if (line == "connectPort") {       string tmp;  iss >> tmp;  sPort = sf::String(tmp);  }
                // else if (line == "networkTeamRed")      readBool(iss, line, bNetworkPlayerI);
                //  show
                else if (line == "showInfoHide")        readBool(iss, line, bShowInfoHide);
                else if (line == "showInfoSB")          readBool(iss, line, bShowInfoSB);
                else if (line == "showInfoDM")          readBool(iss, line, bShowInfoDM);
                else if (line == "showInfoTDM")         readBool(iss, line, bShowInfoTDM);
                else if (line == "showInfoCK")          readBool(iss, line, bShowInfoCK);
                //  UI
                else if (line == "languageID")          readInt(iss, iLanguageID);
                else if (line == "showSelectLanguage")  readBool(iss, line, bShowSelectLanguage);
                else if (line == "showToolTips")        readBool(iss, line, bShowToolTips);
                //  UI new
                else if (line == "NoConfirmations")     readBool(iss, line, bNoConfirmations);
                else if (line == "UIScale")             iss >> UiElement::scale_;
                else if (line == "LogoSigns")           readBool(iss, line, bLogoSigns);
                else if (line == "CountDown")           readInt(iss, iCountDown);

                else if (line == "highStarResolution")  readBool(iss, line, bStarsHigh);
                else if (line == "starField")           readInt(iss, iStarField);
                
                //  post fx
                else if (line == "shaders")             readBool(iss, line, bShaders);
                else if (line == "postFXflashes")       readBool(iss, line, bFlashes);
                //  screen
                else if (line == "resolutionX")         readInt(iss, iResX);
                else if (line == "resolutionY")         readInt(iss, iResY);
                else if (line == "colorDepth")          readInt(iss, iColorDepth);
                else if (line == "antiAliasing")        readInt(iss, iAntiAliasing);
                //  keys
                else if (line == "screenShotKey")       iss >> keyScreenShot;
                else if (line == "statisticsKey")       iss >> keyStatistics;
                else if (line == "screenShotFormat")    iss >> sScreenShotFormat;
                //  audio
                else if (line == "audioRandom")         readBool(iss, line, bAudioRandom);
                else if (line == "audioNextKey")        iss >> keyAudioNext;
                else if (line == "audioPreviousKey")    iss >> keyAudioPrev;
                //  weapons  above
                //  map
                else if (line == "MapXsize")            iss >> iMapXsize;
                else if (line == "MapYsize")            iss >> iMapYsize;
                else if (line == "MapMinPlanets")       iss >> iMapMinPlanets;
                else if (line == "MapMaxPlanets")       iss >> iMapMaxPlanets;
                else if (line == "MapMinPlanetsSize")   iss >> iMapMinPlanetsSize;
                else if (line == "MapMaxPlanetsSize")   iss >> iMapMaxPlanetsSize;
                else if (line == "MapMinPlanetGap")     iss >> iMapMinPlanetGap;

                else if (line == "MapBlackHoles")       iss >> iMapBlackHoles;
                else if (line == "MapSuns")             iss >> iMapSuns;

                else if (line == "MapHomeRadius")       iss >> iMapHomeRadius;
                else if (line == "ShipRadius")          iss >> iShipRadius;
                else if (line == "BallRadius")          iss >> iBallRadius;

                else if (line == "CyclicBorderX")       readBool(iss, line, bCyclicBorderX);
                else if (line == "CyclicBorderY")       readBool(iss, line, bCyclicBorderY);
                else if (line == "GravityScale")        iss >> iGravityScale;
                //  game
                else if (line == "ShipTurnSpeed")       iss >> iShipTurnSpeed;
                else if (line == "DamageScale")         iss >> iDamageScale;
                else if (line == "Regeneration")        iss >> iRegeneration;
                else if (line == "FuelRegen")           iss >> iFuelRegen;
                else if (line == "RespawnDelay")        iss >> iRespawnDelay;
                else if (line == "GlowAlpha")           iss >> iGlowAlpha;
                else
                if (line.substr(0,14) != "enabledWeapons" && line.substr(0,15) != "enabledSpecials")
                    cout << line << " is a bad option in " << sConfigPath << "mars.cfg!\n";
            }
        }else 
            if (save())
                cout << "Created " << sConfigPath << "mars.cfg, using default settings.\n";

        return true;
    }
}
