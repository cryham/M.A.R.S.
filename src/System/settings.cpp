/* settings.cpp

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
#include "defines.hpp"

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
    //  game settings
    //  adjustable via options menu
    //--------------------------------------------------------------------------------------------------------------------------------------------
    int         C_soundVolume =             30;
    int         C_announcerVolume =         0;
    int         C_musicVolume =             60;
    bool        C_showFPS =                 false;
    bool        C_showParticleCount =       false;
    bool        C_showLatency =             false;
    bool        C_fullScreen =              false;
    bool        C_vsync =                   true;

    bool        C_adaptiveParticleCount =   false;
    int         C_globalParticleCount =     100;
    int         C_globalParticleLifeTime =  100;
    bool        C_StarsHigh =               true;
    int         C_StarField =               500;

    int         C_botsLeft =                4;
    int         C_botsRight =               4;
    int         C_botsDeath =               10;
    int         C_pointLimitSB =            10;
    int         C_pointLimitCK =            10;
    int         C_pointLimitDM =            20;
    int         C_pointLimitTDM =           50;

    int         C_powerUpRate =             40;
    int         C_slowMoKickIn =            3;
    int         C_gameSpeed =               100;

    bool        C_showInfoHide =            true;
    bool        C_showInfoSB =              true;
    bool        C_showInfoDM =              true;
    bool        C_showInfoTDM =             true;
    bool        C_showInfoCK =              true;
    bool        C_showSelectLanguage =      true;
    bool        C_showToolTips =            true;

    bool        C_noConfirmations =         true;

    int         C_languageID =              0;
    int         C_resX =                    INITIAL_WINDOW_X;
    int         C_resY =                    INITIAL_WINDOW_Y;
    int         C_colorDepth =              32;
    bool        C_shaders =                 false;
    Key         C_screenShotKey =           Key(sf::Keyboard::F12);

    bool        C_audioRandom =             true;
    Key         C_audioNextKey =            Key(sf::Keyboard::F8);
    Key         C_audioPreviousKey =        Key(sf::Keyboard::F7);
    Key         C_statisticsKey =           Key(sf::Keyboard::Tab);

    std::string C_configPath =              "";
    std::string C_dataPath =                "";
    std::string C_screenShotFormat =        "jpg";

    //  map setup
    int         C_MapMinPlanets      = 1;  // 1
    int         C_MapMaxPlanets      = 4;  // 4
    int         C_MapMinPlanetsSize  = 50;  // 50
    int         C_MapMaxPlanetsSize  = 120;  // 120

    int         C_MapMinPlanetGap    = 150;  // 150
    int         C_MapHomeRadius      = 100;

    int         C_ShipRadius         = 18;  // 18.f
    int         C_MapXsize           = 1440; // 1440
    int         C_MapYsize           = 810;  // 810
    int         C_MapYaspect         = 1000 * 1440 / 810;  // / 1000 = 1

    //  weapons
    int         C_EnabledWeapons =          weapons::wNoWeapon-1;  // all
    int         C_EnabledSpecials =         specials::sNoSpecial-1;
    int         C_EnabledWeaponsByUser =    C_EnabledWeapons;
    int         C_EnabledSpecialsByUser =   C_EnabledSpecials;


    //  player settings ----- adjustable via options menu
    sf::String    C_playerIName =           "PlayerI";
    Color3f       C_playerIColor =          Color3f(1.f, 0.87f, 0.0125f);
    Color3f       C_playerITeamColor =      Color3f(0.94f, 0.24f, 1.f);
    
    Key           C_playerIup =             Key(sf::Keyboard::Up);
    Key           C_playerIdown =           Key(sf::Keyboard::Down);
    Key           C_playerIboost =          Key(sf::Keyboard::RAlt);

    Key           C_playerIleft =           Key(sf::Keyboard::Left);
    Key           C_playerIright =          Key(sf::Keyboard::Right);
    Key           C_playerIfire =           Key(sf::Keyboard::RControl);

    Key           C_playerISpecialKey =     Key(sf::Keyboard::RShift);
    Key           C_playerIprev =           Key(sf::Keyboard::Divide);
    Key           C_playerInext =           Key(sf::Keyboard::Multiply);

    bool          C_playerIteamL =          false;
    bool          C_playerIteamR =          true;
    int           C_playerIShip =           0;

    weapons::WeaponType   C_playerIWeapon =  weapons::wAFK47;
    specials::SpecialType C_playerISpecial = specials::sHeal;
    
    sf::String    C_playerIIName =          "PlayerII";
    Color3f       C_playerIIColor =         Color3f(0.5f, 0.4f, 0.82f);
    Color3f       C_playerIITeamColor =     Color3f(0.05f, 1.f, 0.785f);

    Key           C_playerIIup =            Key(sf::Keyboard::W);
    Key           C_playerIIdown =          Key(sf::Keyboard::S);
    Key           C_playerIIboost =         Key(sf::Keyboard::LAlt);

    Key           C_playerIIleft =          Key(sf::Keyboard::A);
    Key           C_playerIIright =         Key(sf::Keyboard::D);
    Key           C_playerIIfire =          Key(sf::Keyboard::LControl);

    Key           C_playerIISpecialKey =    Key(sf::Keyboard::LShift);
    Key           C_playerIIprev =          Key(sf::Keyboard::Num1);
    Key           C_playerIInext =          Key(sf::Keyboard::Num2);

    bool          C_playerIIteamL =         true;
    bool          C_playerIIteamR =         false;
    int           C_playerIIShip =          0;

    weapons::WeaponType   C_playerIIWeapon =  weapons::wAFK47;
    specials::SpecialType C_playerIISpecial = specials::sHeal;
    bool          C_networkPlayerI =        true;


    //  ai settings ------ adjustable via options menu
    bool        C_drawBotJobs =             false;
    bool        C_drawZones =               false;
    bool        C_drawAIPath =              false;
    int         C_iDumb =                   70;

    //  network settings ----- adjustable via options menu
    sf::String C_ip =                      "192.168.0.1";
    sf::String C_port =                    "12345";


    //  utility
    //--------------------------------------------------------------------------------------------------------------------------------------------

    //  bool
    void readBool(std::istringstream& iss, std::string inputLine, bool& val)
    {
        std::string s;  iss >> s;
        if (s == "true")   val = true;
        else
        if (s == "false")  val = false;
        else
            std::cout << s << " is a bad value for " << inputLine << ". Use true or false instead.\n";
    }

    std::string strBool(bool val)
    {
        return val ? "true" : "false";
    }

    //  int
    void readInt(std::istringstream& iss, int& val, int intMin, int intMax)
    {
        int value;
        iss >> value;
        val = clamp(value, intMin, intMax);
    }

    void readInt(std::istringstream& iss, int& val)
    {
        int value;
        iss >> value;
        val = value;
    }

    //  string
    void readString(std::istringstream& iss, sf::String& val, int len)
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

    void strMax(std::ofstream& outStream, const sf::String& str, int maxLen)
    {
        int i = 0;
        while (i < maxLen && i < str.getSize())
        {
            outStream << str[i] << " ";
            ++i;
        }
        outStream << "0" << std::endl;
    }

    //  color
    void readColor(std::istringstream& iss, Color3f& clr)
    {
        float r,g,b;
        iss >> r >> g >> b;
        clr = Color3f(r,g,b);
    }

    void strColor(std::ofstream& outStream, const Color3f& clr)
    {
        outStream <<  clr.r() << " "<< clr.g() << " " << clr.b() << std::endl;
    }


    //  SAVE
    //--------------------------------------------------------------------------------------------------------------------------------------------
    bool save()
    {
        std::ofstream outStream((C_configPath + "mars.cfg").c_str());

        if (outStream)
        {
            outStream << "// mars config file" << std::endl;
            outStream << "// nearly all these options can be changed with the in-game menu, too." << std::endl << std::endl;

            outStream << "[soundVolume] "           << C_soundVolume << std::endl;
            outStream << "[announcerVolume] "       << C_announcerVolume << std::endl;
            outStream << "[musicVolume] "           << C_musicVolume << std::endl;
            outStream << "[globalParticleCount] "   << C_globalParticleCount << std::endl;
            outStream << "[globalParticleLifeTime] "<< C_globalParticleLifeTime << std::endl;
            
            outStream << "[showFPS] "               << strBool(C_showFPS) << std::endl;
            outStream << "[showParticleCount] "     << strBool(C_showParticleCount) << std::endl;
            outStream << "[showLatency] "           << strBool(C_showLatency) << std::endl;
            outStream << "[fullScreen] "            << strBool(C_fullScreen) << std::endl;
            outStream << "[vsync] "                 << strBool(C_vsync) << std::endl;
            
            outStream << "[drawAIPath] "            << strBool(C_drawAIPath) << std::endl;
            outStream << "[iDumb] "                 << C_iDumb << std::endl;
            outStream << "[adaptiveParticleCount] " << strBool(C_adaptiveParticleCount) << std::endl;
            outStream << "[drawBotJobs] "           << strBool(C_drawBotJobs) << std::endl;
            outStream << "[drawZones] "             << strBool(C_drawZones) << std::endl;
            
            outStream << "[botsLeft] "              << C_botsLeft << std::endl;
            outStream << "[botsRight] "             << C_botsRight << std::endl;
            outStream << "[botsDeath] "             << C_botsDeath << std::endl;
            outStream << "[pointLimitSB] "          << C_pointLimitSB << std::endl;
            outStream << "[pointLimitCK] "          << C_pointLimitCK << std::endl;
            outStream << "[pointLimitDM] "          << C_pointLimitDM << std::endl;
            outStream << "[pointLimitTDM] "         << C_pointLimitTDM << std::endl;
            
            outStream << "[powerUpRate] "           << C_powerUpRate << std::endl;
            outStream << "[slowMoKickIn] "          << C_slowMoKickIn << std::endl;
            outStream << "[gameSpeed] "             << C_gameSpeed << std::endl;
            
            outStream << "[playerIName] ";          strMax(outStream, C_playerIName, 12);

            outStream << "[playerIKeys] "           <<  C_playerIup << " " << C_playerIright << " " << C_playerIleft << " "
                << C_playerIfire << " " << C_playerISpecialKey << " "
                << C_playerIdown << " " << C_playerIboost << " " << C_playerIprev << " " << C_playerInext << std::endl;
            
            outStream << "[playerIColor] ";         strColor(outStream, C_playerIColor);
            outStream << "[playerITeamColor] ";     strColor(outStream, C_playerITeamColor);
            outStream << "[playerITeamL] "          << strBool(C_playerIteamL) << std::endl;
            outStream << "[playerITeamR] "          << strBool(C_playerIteamR) << std::endl;
            outStream << "[playerIShip] "           <<  C_playerIShip << std::endl;
            outStream << "[playerIWeapon] "         <<  C_playerIWeapon << std::endl;
            outStream << "[playerISpecial] "        <<  C_playerISpecial << std::endl;
            
            outStream << "[playerIIName] ";         strMax(outStream, C_playerIIName, 12);
            outStream << "[playerIIKeys] "          <<  C_playerIIup << " "<< C_playerIIright << " " << C_playerIIleft << " "
                << C_playerIIfire << " " << C_playerIISpecialKey << " "
                << C_playerIIdown << " " << C_playerIIboost << " " << C_playerIIprev << " " << C_playerIInext << std::endl;

            outStream << "[playerIIColor] ";        strColor(outStream, C_playerIIColor);
            outStream << "[playerIITeamColor] ";    strColor(outStream, C_playerIITeamColor);
            outStream << "[playerIITeamL] "         << strBool(C_playerIIteamL) << std::endl;
            outStream << "[playerIITeamR] "         << strBool(C_playerIIteamR) << std::endl;
            outStream << "[playerIIShip] "          <<  C_playerIIShip << std::endl;
            outStream << "[playerIIWeapon] "        <<  C_playerIIWeapon << std::endl;
            outStream << "[playerIISpecial] "       <<  C_playerIISpecial << std::endl;
            
            outStream << "[connectIP] "             <<  C_ip.toAnsiString() << std::endl;
            outStream << "[connectPort] "           <<  C_port.toAnsiString() << std::endl;
            outStream << "[networkTeamRed] "        << strBool(C_networkPlayerI) << std::endl;
            
            outStream << "[showInfoHide] "          << strBool(C_showInfoHide) << std::endl;
            outStream << "[showInfoSB] "            << strBool(C_showInfoSB) << std::endl;
            outStream << "[showInfoDM] "            << strBool(C_showInfoDM) << std::endl;
            outStream << "[showInfoTDM] "           << strBool(C_showInfoTDM) << std::endl;
            outStream << "[showInfoCK] "            << strBool(C_showInfoCK) << std::endl;
            
            outStream << "[showSelectLanguage] "    << strBool(C_showSelectLanguage) << std::endl;
            outStream << "[showToolTips] "          << strBool(C_showToolTips) << std::endl;
            outStream << "[languageID] "            <<  C_languageID << std::endl;
            outStream << "[highStarResolution] "    << strBool(C_StarsHigh) << std::endl;
            outStream << "[starField] "             <<  C_StarField << std::endl;
            
            outStream << "[shaders] "               << strBool(C_shaders) << std::endl;
            outStream << "[resolutionX] "           << C_resX << std::endl;
            outStream << "[resolutionY] "           << C_resY << std::endl;
            outStream << "[colorDepth] "            << C_colorDepth << std::endl;
            
            outStream << "[audioRandom] "           << strBool(C_audioRandom) << std::endl;
            outStream << "[audioNextKey] "          << C_audioNextKey << std::endl;
            outStream << "[audioPreviousKey] "      << C_audioPreviousKey << std::endl;
            outStream << "[screenShotKey] "         << C_screenShotKey << std::endl;
            outStream << "[statisticsKey] "         << C_statisticsKey << std::endl;
            outStream << "[screenShotFormat] "      << C_screenShotFormat << std::endl;
            
            outStream << "[enabledWeapons] "        << C_EnabledWeaponsByUser << std::endl;
            outStream << "[enabledSpecials] "       << C_EnabledSpecialsByUser << std::endl;

            outStream << "[MapXsize] "              << C_MapXsize << std::endl;
            outStream << "[MapYsize] "              << C_MapYsize << std::endl;
            outStream << "[MapMinPlanets] "         << C_MapMinPlanets << std::endl;
            outStream << "[MapMaxPlanets] "         << C_MapMaxPlanets << std::endl;
            outStream << "[MapMinPlanetsSize] "     << C_MapMinPlanetsSize << std::endl;
            outStream << "[MapMaxPlanetsSize] "     << C_MapMaxPlanetsSize << std::endl;
            outStream << "[MapMinPlanetGap] "       << C_MapMinPlanetGap << std::endl;
            outStream << "[MapHomeRadius] "         << C_MapHomeRadius << std::endl;
            outStream << "[ShipRadius] "            << C_ShipRadius << std::endl;

            outStream.close();
            return true;
        }
        else
        {
            std::cout << "Faild to save configuration file " << C_configPath << "mars.cfg!" << std::endl;
            return false;
        }
    }

    //  LOAD
    //--------------------------------------------------------------------------------------------------------------------------------------------
    bool load()
    {
        // check whether application directory in the home diretory exists, if not create it
        #ifdef __linux__
            std::string home(getenv("HOME"));
            if (*home.rbegin() != '/') home += '/';
            mkdir((home + ".marsshooter/").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif

        #if defined(__WIN32__) || defined(_WIN32)
            TCHAR szAppData[MAX_PATH];
            SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
            std::string home(szAppData);
            CreateDirectory((home + "/.marsshooter/").c_str(), NULL);
        #endif

        #ifdef __APPLE__
            std::string home(getenv("HOME"));
            if (*home.rbegin() != '/') home += '/';
            mkdir((home + "Library/Preferences/mars/").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif

        // search for config file
        if (C_configPath == "")
        {
            bool success(false);
            std::cout << "Searching for configuration file... " << std::flush;
            C_configPath = "./";

            #ifdef __linux__
                std::string home(getenv("HOME"));
                if (*home.rbegin() != '/') home += '/';

                if (std::ifstream((C_configPath + "mars.cfg").c_str()))
                    success = true;
                else if (std::ifstream((home + ".marsshooter/mars.cfg").c_str()))
                {
                    C_configPath =      home + ".marsshooter/";
                    success = true;
                }else
                    C_configPath =      home + ".marsshooter/";
            #endif

            #if defined(__WIN32__) || defined(_WIN32)
                TCHAR szAppData[MAX_PATH];
                SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
                std::string home(szAppData);

                if (std::ifstream((C_configPath + "mars.cfg").c_str()))
                    success = true;
                else if (std::ifstream((home + "/.marsshooter/mars.cfg").c_str()))
                {
                    C_configPath =      home + "/.marsshooter/";
                    success = true;
                }else
                    C_configPath =      home + "/.marsshooter/";
            #endif

            #ifdef __APPLE__
                std::string home(getenv("HOME"));
                if (*home.rbegin() != '/') home += '/';

                if (std::ifstream((home + "Library/Preferences/mars/mars.cfg").c_str()))
                {
                    C_configPath =      home + "Library/Preferences/mars/";
                    success = true;
                }else
                    C_configPath =      home + "Library/Preferences/mars/";
            #endif

            if (success) std::cout << "Found " << C_configPath << "mars.cfg"  << std::endl;
            else         std::cout << "Found nothing. Will create a new one." << std::endl;
        }

        // search for data files
        if (C_dataPath == "")
        {
            bool success(false);
            std::cout << "Searching for data files... " << std::flush;
            C_dataPath = "./data/";

            #ifdef __linux__
                if (std::ifstream((C_dataPath + "locales/English.txt").c_str()))
                    success = true;
                else if (std::ifstream("/usr/share/marsshooter/locales/English.txt")) {
                    C_dataPath = "/usr/share/marsshooter/";
                    success = true;
                } else if (std::ifstream("/usr/share/games/marsshooter/locales/English.txt")) {
                    C_dataPath = "/usr/share/games/marsshooter/";
                    success = true;
                } else if (std::ifstream("/usr/local/share/games/marsshooter/locales/English.txt")) {
                    C_dataPath = "/usr/local/share/games/marsshooter/";
                    success = true;
                } else if (std::ifstream("/usr/local/share/marsshooter/locales/English.txt")) {
                    C_dataPath = "/usr/local/share/marsshooter/";
                    success = true;
                } else if (std::ifstream("/usr/local/games/marsshooter/locales/English.txt")) {
                    C_dataPath = "/usr/local/games/marsshooter/";
                    success = true;
                }
            #endif

            #if defined(__WIN32__) || defined(_WIN32)
                if (std::ifstream((C_dataPath + "locales/English.txt").c_str()))
                    success = true;
            #endif

            #ifdef __APPLE__
                if (std::ifstream("../Resources/data/locales/English.txt")) {
                    C_dataPath = "../Resources/data/";
                    success = true;
                }
            #endif

            if (success)
                std::cout << "Found " << C_dataPath << std::endl;
            else
            {   std::cout << "Found nothing. Aborting." << std::endl;
                return false;
            }
        }

        //  read lines
        std::vector<sf::String> lines;
        if (file::load(C_configPath + "mars.cfg", lines))
        {
            for (auto& it : lines)
            {
                std::istringstream iss (it.toAnsiString());
                std::string inputLine;
                iss >> inputLine;
                
                if      (inputLine == "[soundVolume]")            readInt(iss, C_soundVolume, 0, 100);
                else if (inputLine == "[announcerVolume]")        readInt(iss, C_announcerVolume, 0, 100);
                else if (inputLine == "[musicVolume]")            readInt(iss, C_musicVolume, 0, 100);
                
                else if (inputLine == "[globalParticleCount]")    readInt(iss, C_globalParticleCount, 10, 300);
                else if (inputLine == "[globalParticleLifeTime]") readInt(iss, C_globalParticleLifeTime, 10, 300);
                
                else if (inputLine == "[showFPS]")                readBool(iss, inputLine, C_showFPS);
                else if (inputLine == "[showParticleCount]")      readBool(iss, inputLine, C_showParticleCount);
                else if (inputLine == "[showLatency]")            readBool(iss, inputLine, C_showLatency);
                
                else if (inputLine == "[fullScreen]")             readBool(iss, inputLine, C_fullScreen);
                else if (inputLine == "[vsync]")                  readBool(iss, inputLine, C_vsync);
                
                else if (inputLine == "[drawAIPath]")             readBool(iss, inputLine, C_drawAIPath);
                else if (inputLine == "[iDumb]")                  readInt(iss, C_iDumb, 0, 100);

                else if (inputLine == "[adaptiveParticleCount]")  readBool(iss, inputLine, C_adaptiveParticleCount);
                else if (inputLine == "[drawBotJobs]")            readBool(iss, inputLine, C_drawBotJobs);
                else if (inputLine == "[drawZones]")              readBool(iss, inputLine, C_drawZones);
                
                else if (inputLine == "[botsLeft]")               readInt(iss, C_botsLeft, 0, 20);
                else if (inputLine == "[botsRight]")              readInt(iss, C_botsRight, 0, 20);
                else if (inputLine == "[botsDeath]")              readInt(iss, C_botsDeath, 0, 50);
                else if (inputLine == "[pointLimitSB]")           readInt(iss, C_pointLimitSB, 1, 100);
                else if (inputLine == "[pointLimitCK]")           readInt(iss, C_pointLimitCK, 1, 100);
                else if (inputLine == "[pointLimitDM]")           readInt(iss, C_pointLimitDM, 1, 100);
                else if (inputLine == "[pointLimitTDM]")          readInt(iss, C_pointLimitTDM,1, 100);

                else if (inputLine == "[powerUpRate]")            readInt(iss, C_powerUpRate, 0, 100);
                else if (inputLine == "[slowMoKickIn]")           readInt(iss, C_slowMoKickIn, 0, 100);
                else if (inputLine == "[gameSpeed]")              readInt(iss, C_gameSpeed, 50, 200);

                else if (inputLine == "[playerIName]")            readString(iss, C_playerIName, 12);
                else if (inputLine == "[playerIIName]")           readString(iss, C_playerIIName, 12);
                else if (inputLine == "[playerIKeys]") {
                    iss >> C_playerIup >> C_playerIright >> C_playerIleft >> C_playerIfire >> C_playerISpecialKey;
                    iss >> C_playerIdown >> C_playerIboost >> C_playerIprev >> C_playerInext;
                }
                else if (inputLine == "[playerIIKeys]") {
                    iss >> C_playerIIup >> C_playerIIright >> C_playerIIleft >> C_playerIIfire >> C_playerIISpecialKey;
                    iss >> C_playerIIdown >> C_playerIIboost >> C_playerIIprev >> C_playerIInext;
                }
                else if (inputLine == "[playerIColor]")       readColor(iss, C_playerIColor);
                else if (inputLine == "[playerIIColor]")      readColor(iss, C_playerIIColor);
                else if (inputLine == "[playerITeamColor]")   readColor(iss, C_playerITeamColor);
                else if (inputLine == "[playerIITeamColor]")  readColor(iss, C_playerIITeamColor);
                else if (inputLine == "[playerITeamL]")       readBool(iss, inputLine, C_playerIteamL);
                else if (inputLine == "[playerITeamR]")       readBool(iss, inputLine, C_playerIteamR);
                else if (inputLine == "[playerIShip]")        iss >> C_playerIShip;
                else if (inputLine == "[playerIIShip]")       iss >> C_playerIIShip;

                else if (inputLine == "[playerIWeapon]") {    int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    C_playerIWeapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (inputLine == "[playerISpecial]") {   int tmp;  iss >> tmp;
                    C_playerISpecial = static_cast<specials::SpecialType>(tmp);
                }
                else if (inputLine == "[playerIIWeapon]") {   int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    C_playerIIWeapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (inputLine == "[playerIISpecial]") {  int tmp;  iss >> tmp;
                    C_playerIISpecial = static_cast<specials::SpecialType>(tmp);
                }

                else if (inputLine == "[playerIITeamL]")       readBool(iss, inputLine, C_playerIIteamL);
                else if (inputLine == "[playerIITeamR]")       readBool(iss, inputLine, C_playerIIteamR);
                
                else if (inputLine == "[connectIP]") {         std::string tmp;  iss >> tmp;  C_ip = sf::String(tmp);    }
                else if (inputLine == "[connectPort]") {       std::string tmp;  iss >> tmp;  C_port = sf::String(tmp);  }
                else if (inputLine == "[languageID]")          readInt(iss, C_languageID);

                else if (inputLine == "[networkTeamRed]")      readBool(iss, inputLine, C_networkPlayerI);
                else if (inputLine == "[showInfoHide]")        readBool(iss, inputLine, C_showInfoHide);
                else if (inputLine == "[showInfoSB]")          readBool(iss, inputLine, C_showInfoSB);
                else if (inputLine == "[showInfoDM]")          readBool(iss, inputLine, C_showInfoDM);
                else if (inputLine == "[showInfoTDM]")         readBool(iss, inputLine, C_showInfoTDM);
                else if (inputLine == "[showInfoCK]")          readBool(iss, inputLine, C_showInfoCK);
                else if (inputLine == "[showToolTips]")        readBool(iss, inputLine, C_showToolTips);
                else if (inputLine == "[highStarResolution]")  readBool(iss, inputLine, C_StarsHigh);

                else if (inputLine == "[starField]")           readInt(iss, C_StarField);
                else if (inputLine == "[showSelectLanguage]")  readBool(iss, inputLine, C_showSelectLanguage);
                else if (inputLine == "[shaders]")             readBool(iss, inputLine, C_shaders);
                else if (inputLine == "[resolutionX]")         readInt(iss, C_resX);
                else if (inputLine == "[resolutionY]")         readInt(iss, C_resY);
                else if (inputLine == "[colorDepth]")          readInt(iss, C_colorDepth);
                
                else if (inputLine == "[audioRandom]")         readBool(iss, inputLine, C_audioRandom);
                else if (inputLine == "[audioNextKey]")        iss >> C_audioNextKey;
                else if (inputLine == "[audioPreviousKey]")    iss >> C_audioPreviousKey;
                else if (inputLine == "[screenShotKey]")       iss >> C_screenShotKey;
                else if (inputLine == "[statisticsKey]")       iss >> C_statisticsKey;
                else if (inputLine == "[screenShotFormat]")    iss >> C_screenShotFormat;

                else if (inputLine == "[enabledWeapons]"){     iss >> C_EnabledWeaponsByUser;   C_EnabledWeapons = C_EnabledWeaponsByUser;    }
                else if (inputLine == "[enabledSpecials]") {   iss >> C_EnabledSpecialsByUser;  C_EnabledSpecials = C_EnabledSpecialsByUser;  }

                else if (inputLine == "[MapXsize]")            iss >> C_MapXsize;
                else if (inputLine == "[MapYsize]")            iss >> C_MapYsize;
                else if (inputLine == "[MapMinPlanets]")       iss >> C_MapMinPlanets;
                else if (inputLine == "[MapMaxPlanets]")       iss >> C_MapMaxPlanets;
                else if (inputLine == "[MapMinPlanetsSize]")   iss >> C_MapMinPlanetsSize;
                else if (inputLine == "[MapMaxPlanetsSize]")   iss >> C_MapMaxPlanetsSize;
                else if (inputLine == "[MapMinPlanetGap]")     iss >> C_MapMinPlanetGap;
                else if (inputLine == "[MapHomeRadius]")       iss >> C_MapHomeRadius;
                else if (inputLine == "[ShipRadius]")          iss >> C_ShipRadius;

                else
                    std::cout << inputLine << " is a bad option in " << C_configPath << "mars.cfg!\n";
            }
        }
        else 
        {
            if (save())
                std::cout << "Created " << C_configPath << "mars.cfg, using default settings.\n";
        }
        return true;
    }
}
