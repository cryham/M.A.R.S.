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
    //  game settings
    //  adjustable via options menu
    //----------------------------------------------------------------------------------------------------------------------------------
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
    //  bots
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
    // int         C_UIscale =                 100;  // UiElement::scale_
    bool        C_LogoSigns =               true;
    int         C_CountDown =               3;

    int         C_languageID =              0;
    //  screen
    int         C_resX =                    INITIAL_WINDOW_X;
    int         C_resY =                    INITIAL_WINDOW_Y;
    int         C_colorDepth =              32;
    //  post fx
    bool        C_shaders =                 false;
    bool        C_Flashes =                 false;
    Key         C_screenShotKey =           Key(sf::Keyboard::F12);
    //  audio
    bool        C_audioRandom =             true;
    Key         C_audioNextKey =            Key(sf::Keyboard::F8);
    Key         C_audioPreviousKey =        Key(sf::Keyboard::F7);
    Key         C_statisticsKey =           Key(sf::Keyboard::Tab);

    string      C_configPath =              "";
    string      C_dataPath =                "";
    string      C_screenShotFormat =        "jpg";

    //  map setup
    int         C_MapMinPlanets      = 1;
    int         C_MapMaxPlanets      = 4;
    int         C_MapMinPlanetsSize  = 50;
    int         C_MapMaxPlanetsSize  = 120;

    int         C_MapMinPlanetGap    = 150;
    int         C_MapHomeRadius      = 100;

    int         C_ShipRadius         = 18;
    int         C_MapXsize           = 1440;
    int         C_MapYsize           = 810;
    // int      C_MapYaspect         = 1000 * 1440 / 810;  // / 1000 = 1
    int         C_BallRadius         = 15;

    int         C_ShipTurnSpeed = 25;
    int         C_DamageScale   = 50;
    int         C_Regeneration  = 60;
    int         C_FuelRegen     = 50;
    int         C_RespawnDelay  = 20;
    int         C_GlowAlpha     = 20;

    bool        C_CyclicBorderX = true;
    bool        C_CyclicBorderY = true;
    int         C_GravityScale  = 100;

    //  weapons
    bool        C_EnabledWeapons[weapons::All] = {true,};
    bool        C_EnabledWeaponsByUser[weapons::All] = {true,};
    bool        C_EnabledSpecials[specials::All] =  {true,};
    bool        C_EnabledSpecialsByUser[specials::All] = {true,};


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
    bool          C_playerImouseAim =       true;

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
    bool          C_playerIImouseAim =      false;

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
    //----------------------------------------------------------------------------------------------------------------------------------

    //  bool
    void readBool(istringstream& iss, string inputLine, bool& val)
    {
        string s;  iss >> s;
        if (s == "true")   val = true;
        else
        if (s == "false")  val = false;
        else
            cout << s << " is a bad value for " << inputLine << ". Use true or false instead.\n";
    }

    string strBool(bool val)
    {
        return val ? "true" : "false";
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
        ofstream oss((C_configPath + "mars.cfg").c_str());
        if (oss)
        {
            oss << "// mars config file" << endl;
            oss << "// nearly all these options can be changed with the in-game menu, too." << endl << endl;

            oss << "[soundVolume] "           << C_soundVolume << endl;
            oss << "[announcerVolume] "       << C_announcerVolume << endl;
            oss << "[musicVolume] "           << C_musicVolume << endl;
            oss << "[globalParticleCount] "   << C_globalParticleCount << endl;
            oss << "[globalParticleLifeTime] "<< C_globalParticleLifeTime << endl;
            
            oss << "[showFPS] "               << strBool(C_showFPS) << endl;
            oss << "[showParticleCount] "     << strBool(C_showParticleCount) << endl;
            oss << "[showLatency] "           << strBool(C_showLatency) << endl;
            oss << "[fullScreen] "            << strBool(C_fullScreen) << endl;
            oss << "[vsync] "                 << strBool(C_vsync) << endl;
            
            oss << "[drawAIPath] "            << strBool(C_drawAIPath) << endl;
            oss << "[iDumb] "                 << C_iDumb << endl;
            oss << "[adaptiveParticleCount] " << strBool(C_adaptiveParticleCount) << endl;
            oss << "[drawBotJobs] "           << strBool(C_drawBotJobs) << endl;
            oss << "[drawZones] "             << strBool(C_drawZones) << endl;
            //  points
            oss << "[botsLeft] "              << C_botsLeft << endl;
            oss << "[botsRight] "             << C_botsRight << endl;
            oss << "[botsDeath] "             << C_botsDeath << endl;
            oss << "[pointLimitSB] "          << C_pointLimitSB << endl;
            oss << "[pointLimitCK] "          << C_pointLimitCK << endl;
            oss << "[pointLimitDM] "          << C_pointLimitDM << endl;
            oss << "[pointLimitTDM] "         << C_pointLimitTDM << endl;
            
            oss << "[powerUpRate] "           << C_powerUpRate << endl;
            oss << "[slowMoKickIn] "          << C_slowMoKickIn << endl;
            oss << "[gameSpeed] "             << C_gameSpeed << endl;
            //----  player I
            oss << "[playerIName] ";          strMax(oss, C_playerIName, 12);
            oss << "[playerIKeys] "           <<  C_playerIup << " " << C_playerIright << " " << C_playerIleft << " "
                << C_playerIfire << " " << C_playerISpecialKey << " "
                << C_playerIdown << " " << C_playerIboost << " " << C_playerIprev << " " << C_playerInext << endl;
            
            oss << "[playerIColor] ";         strColor(oss, C_playerIColor);
            oss << "[playerITeamColor] ";     strColor(oss, C_playerITeamColor);
            oss << "[playerITeamL] "          << strBool(C_playerIteamL) << endl;
            oss << "[playerITeamR] "          << strBool(C_playerIteamR) << endl;
            
            oss << "[playerIShip] "           <<  C_playerIShip << endl;
            oss << "[playerIWeapon] "         <<  C_playerIWeapon << endl;
            oss << "[playerISpecial] "        <<  C_playerISpecial << endl;
            oss << "[playerImouseAim] "       << strBool(C_playerImouseAim) << endl;
            //  player II
            oss << "[playerIIName] ";         strMax(oss, C_playerIIName, 12);
            oss << "[playerIIKeys] "          <<  C_playerIIup << " "<< C_playerIIright << " " << C_playerIIleft << " "
                << C_playerIIfire << " " << C_playerIISpecialKey << " "
                << C_playerIIdown << " " << C_playerIIboost << " " << C_playerIIprev << " " << C_playerIInext << endl;

            oss << "[playerIIColor] ";        strColor(oss, C_playerIIColor);
            oss << "[playerIITeamColor] ";    strColor(oss, C_playerIITeamColor);
            oss << "[playerIITeamL] "         << strBool(C_playerIIteamL) << endl;
            oss << "[playerIITeamR] "         << strBool(C_playerIIteamR) << endl;
            
            oss << "[playerIIShip] "          <<  C_playerIIShip << endl;
            oss << "[playerIIWeapon] "        <<  C_playerIIWeapon << endl;
            oss << "[playerIISpecial] "       <<  C_playerIISpecial << endl;
            oss << "[playerIImouseAim] "      << strBool(C_playerIImouseAim) << endl;
            //----
            oss << "[connectIP] "             << C_ip.toAnsiString() << endl;
            oss << "[connectPort] "           << C_port.toAnsiString() << endl;
            oss << "[networkTeamRed] "        << strBool(C_networkPlayerI) << endl;
            //  show
            oss << "[showInfoHide] "          << strBool(C_showInfoHide) << endl;
            oss << "[showInfoSB] "            << strBool(C_showInfoSB) << endl;
            oss << "[showInfoDM] "            << strBool(C_showInfoDM) << endl;
            oss << "[showInfoTDM] "           << strBool(C_showInfoTDM) << endl;
            oss << "[showInfoCK] "            << strBool(C_showInfoCK) << endl;

            //  UI
            oss << "[languageID] "            << C_languageID << endl;
            oss << "[showSelectLanguage] "    << strBool(C_showSelectLanguage) << endl;
            oss << "[showToolTips] "          << strBool(C_showToolTips) << endl;
            //  UI new
            oss << "[NoConfirmations] "       << strBool(C_noConfirmations) << endl;
            oss << "[UIScale] "               << UiElement::scale_ << endl;
            oss << "[C_LogoSigns] "           << strBool(C_LogoSigns) << endl;
            oss << "[C_CountDown] "           << C_CountDown << endl;

            oss << "[highStarResolution] "    << strBool(C_StarsHigh) << endl;
            oss << "[starField] "             << C_StarField << endl;
            
            //  post fx
            oss << "[shaders] "               << strBool(C_shaders) << endl;
            oss << "[postFXflashes] "         << strBool(C_Flashes) << endl;
            //  screen
            oss << "[resolutionX] "           << C_resX << endl;
            oss << "[resolutionY] "           << C_resY << endl;
            oss << "[colorDepth] "            << C_colorDepth << endl;
            //  keys
            oss << "[screenShotKey] "         << C_screenShotKey << endl;
            oss << "[statisticsKey] "         << C_statisticsKey << endl;
            oss << "[screenShotFormat] "      << C_screenShotFormat << endl;
            
            //  audio
            oss << "[audioRandom] "           << strBool(C_audioRandom) << endl;
            oss << "[audioNextKey] "          << C_audioNextKey << endl;
            oss << "[audioPreviousKey] "      << C_audioPreviousKey << endl;
            //  weapons
            for (int i=0; i < weapons::All; ++i)
                oss << "[enabledWeapons"<< i <<"] "  << strBool(C_EnabledWeaponsByUser[i]) << endl;

            for (int i=0; i < specials::All; ++i)
                oss << "[enabledSpecials"<< i <<"] " << strBool(C_EnabledSpecialsByUser[i]) << endl;
            //  map
            oss << "[MapXsize] "              << C_MapXsize << endl;
            oss << "[MapYsize] "              << C_MapYsize << endl;
            oss << "[MapMinPlanets] "         << C_MapMinPlanets << endl;
            oss << "[MapMaxPlanets] "         << C_MapMaxPlanets << endl;
            oss << "[MapMinPlanetsSize] "     << C_MapMinPlanetsSize << endl;
            oss << "[MapMaxPlanetsSize] "     << C_MapMaxPlanetsSize << endl;
            oss << "[MapMinPlanetGap] "       << C_MapMinPlanetGap << endl;

            oss << "[MapHomeRadius] "         << C_MapHomeRadius << endl;
            oss << "[ShipRadius] "            << C_ShipRadius << endl;
            oss << "[BallRadius] "            << C_BallRadius << endl;

            oss << "[CyclicBorderX] "         << strBool(C_CyclicBorderX) << endl;
            oss << "[CyclicBorderY] "         << strBool(C_CyclicBorderY) << endl;
            oss << "[GravityScale] "          << C_GravityScale << endl;
            //  game
            oss << "[ShipTurnSpeed] "         << C_ShipTurnSpeed << endl;
            oss << "[DamageScale] "           << C_DamageScale << endl;
            oss << "[Regeneration] "          << C_Regeneration << endl;
            oss << "[FuelRegen] "             << C_FuelRegen << endl;
            oss << "[RespawnDelay] "          << C_RespawnDelay << endl;
            oss << "[GlowAlpha] "             << C_GlowAlpha << endl;

            oss.close();
            return true;
        }else
        {   cout << "Faild to save configuration file " << C_configPath << "mars.cfg!" << endl;
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
        if (C_configPath == "")
        {
            bool success(false);
            cout << "Searching for configuration file... " << flush;
            C_configPath = "./";

            #ifdef __linux__
                string home(getenv("HOME"));
                if (*home.rbegin() != '/') home += '/';

                if (ifstream((C_configPath + "mars.cfg").c_str()))
                    success = true;
                else if (ifstream((home + ".marsshooter/mars.cfg").c_str()))
                {
                    C_configPath =      home + ".marsshooter/";
                    success = true;
                }else
                    C_configPath =      home + ".marsshooter/";
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

            if (success) cout << "Found " << C_configPath << "mars.cfg"  << endl;
            else         cout << "Found nothing. Will create a new one." << endl;
        }

        // search for data files
        if (C_dataPath == "")
        {
            bool success(false);
            cout << "Searching for data files... " << flush;
            C_dataPath = "./data/";

            #ifdef __linux__
                if (ifstream((C_dataPath + "locales/English.txt").c_str()))
                    success = true;
                else if (ifstream("/usr/share/marsshooter/locales/English.txt"))
                {   C_dataPath = "/usr/share/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/share/games/marsshooter/locales/English.txt"))
                {   C_dataPath = "/usr/share/games/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/share/games/marsshooter/locales/English.txt"))
                {   C_dataPath = "/usr/local/share/games/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/share/marsshooter/locales/English.txt"))
                {   C_dataPath = "/usr/local/share/marsshooter/";
                    success = true;
                }else if (ifstream("/usr/local/games/marsshooter/locales/English.txt"))
                {   C_dataPath = "/usr/local/games/marsshooter/";
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
                cout << "Found " << C_dataPath << endl;
            else
            {   cout << "Found nothing. Aborting." << endl;
                return false;
            }
        }

        //  read lines
        //----------------------------------------------------------------------------------------------------------------------------------
        vector<sf::String> lines;
        if (file::load(C_configPath + "mars.cfg", lines))
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
                    ss << "[enabledWeapons" << i << "]";
                    if (line == ss.str())
                    {
                        readBool(iss, line, C_EnabledWeaponsByUser[i]);   C_EnabledWeapons[i] = C_EnabledWeaponsByUser[i];
                        found = true;
                    }
                }
                if (found)  continue;
                for (int i=0; i < specials::All; ++i)
                {
                    stringstream ss;
                    ss << "[enabledSpecials" << i << "]";
                    if (line == ss.str())
                    {
                        readBool(iss, line, C_EnabledSpecialsByUser[i]);   C_EnabledSpecials[i] = C_EnabledSpecialsByUser[i];
                        found = true;
                    }
                }
                if (found)  continue;

                if      (line == "[soundVolume]")            readInt(iss, C_soundVolume, 0, 100);
                else if (line == "[announcerVolume]")        readInt(iss, C_announcerVolume, 0, 100);
                else if (line == "[musicVolume]")            readInt(iss, C_musicVolume, 0, 100);
                
                else if (line == "[globalParticleCount]")    readInt(iss, C_globalParticleCount, 10, 300);
                else if (line == "[globalParticleLifeTime]") readInt(iss, C_globalParticleLifeTime, 10, 300);
                
                else if (line == "[showFPS]")                readBool(iss, line, C_showFPS);
                else if (line == "[showParticleCount]")      readBool(iss, line, C_showParticleCount);
                else if (line == "[showLatency]")            readBool(iss, line, C_showLatency);
                
                else if (line == "[fullScreen]")             readBool(iss, line, C_fullScreen);
                else if (line == "[vsync]")                  readBool(iss, line, C_vsync);
                
                else if (line == "[drawAIPath]")             readBool(iss, line, C_drawAIPath);
                else if (line == "[iDumb]")                  readInt(iss, C_iDumb, 0, 100);

                else if (line == "[adaptiveParticleCount]")  readBool(iss, line, C_adaptiveParticleCount);
                else if (line == "[drawBotJobs]")            readBool(iss, line, C_drawBotJobs);
                else if (line == "[drawZones]")              readBool(iss, line, C_drawZones);
                //  points
                else if (line == "[botsLeft]")               readInt(iss, C_botsLeft, 0, 20);
                else if (line == "[botsRight]")              readInt(iss, C_botsRight, 0, 20);
                else if (line == "[botsDeath]")              readInt(iss, C_botsDeath, 0, 80);
                else if (line == "[pointLimitSB]")           readInt(iss, C_pointLimitSB, 1, 100);
                else if (line == "[pointLimitCK]")           readInt(iss, C_pointLimitCK, 1, 100);
                else if (line == "[pointLimitDM]")           readInt(iss, C_pointLimitDM, 1, 400);
                else if (line == "[pointLimitTDM]")          readInt(iss, C_pointLimitTDM,1, 400);

                else if (line == "[powerUpRate]")            readInt(iss, C_powerUpRate, 0, 100);
                else if (line == "[slowMoKickIn]")           readInt(iss, C_slowMoKickIn, 0, 100);
                else if (line == "[gameSpeed]")              readInt(iss, C_gameSpeed, 50, 200);
                //----  players
                else if (line == "[playerIName]")            readString(iss, C_playerIName, 12);
                else if (line == "[playerIIName]")           readString(iss, C_playerIIName, 12);
                else if (line == "[playerIKeys]") {
                    iss >> C_playerIup >> C_playerIright >> C_playerIleft >> C_playerIfire >> C_playerISpecialKey;
                    iss >> C_playerIdown >> C_playerIboost >> C_playerIprev >> C_playerInext;
                }
                else if (line == "[playerIIKeys]") {
                    iss >> C_playerIIup >> C_playerIIright >> C_playerIIleft >> C_playerIIfire >> C_playerIISpecialKey;
                    iss >> C_playerIIdown >> C_playerIIboost >> C_playerIIprev >> C_playerIInext;
                }
                else if (line == "[playerIColor]")       readColor(iss, C_playerIColor);
                else if (line == "[playerIIColor]")      readColor(iss, C_playerIIColor);
                else if (line == "[playerITeamColor]")   readColor(iss, C_playerITeamColor);
                else if (line == "[playerIITeamColor]")  readColor(iss, C_playerIITeamColor);
                
                else if (line == "[playerITeamL]")       readBool(iss, line, C_playerIteamL);
                else if (line == "[playerITeamR]")       readBool(iss, line, C_playerIteamR);
                else if (line == "[playerIShip]")        iss >> C_playerIShip;
                else if (line == "[playerIIShip]")       iss >> C_playerIIShip;

                else if (line == "[playerIWeapon]") {    int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    C_playerIWeapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (line == "[playerISpecial]") {   int tmp;  iss >> tmp;
                    C_playerISpecial = static_cast<specials::SpecialType>(tmp);
                }
                else if (line == "[playerIIWeapon]") {   int tmp;  iss >> tmp;
                    if (tmp == weapons::wInsta)
                        tmp = weapons::wAFK47;
                    C_playerIIWeapon = static_cast<weapons::WeaponType>(tmp);
                }
                else if (line == "[playerIISpecial]") {  int tmp;  iss >> tmp;
                    C_playerIISpecial = static_cast<specials::SpecialType>(tmp);
                }
                else if (line == "[playerImouseAim]")     readBool(iss, line, C_playerImouseAim);
                else if (line == "[playerIImouseAim]")    readBool(iss, line, C_playerIImouseAim);

                else if (line == "[playerIITeamL]")       readBool(iss, line, C_playerIIteamL);
                else if (line == "[playerIITeamR]")       readBool(iss, line, C_playerIIteamR);
                //----
                else if (line == "[connectIP]") {         string tmp;  iss >> tmp;  C_ip = sf::String(tmp);    }
                else if (line == "[connectPort]") {       string tmp;  iss >> tmp;  C_port = sf::String(tmp);  }
                else if (line == "[networkTeamRed]")      readBool(iss, line, C_networkPlayerI);
                //  show
                else if (line == "[showInfoHide]")        readBool(iss, line, C_showInfoHide);
                else if (line == "[showInfoSB]")          readBool(iss, line, C_showInfoSB);
                else if (line == "[showInfoDM]")          readBool(iss, line, C_showInfoDM);
                else if (line == "[showInfoTDM]")         readBool(iss, line, C_showInfoTDM);
                else if (line == "[showInfoCK]")          readBool(iss, line, C_showInfoCK);
                //  UI
                else if (line == "[languageID]")          readInt(iss, C_languageID);
                else if (line == "[showSelectLanguage]")  readBool(iss, line, C_showSelectLanguage);
                else if (line == "[showToolTips]")        readBool(iss, line, C_showToolTips);
                //  UI new
                else if (line == "[NoConfirmations]")     readBool(iss, line, C_noConfirmations);
                else if (line == "[UIScale]")             iss >> UiElement::scale_;
                else if (line == "[C_LogoSigns]")         readBool(iss, line, C_LogoSigns);
                else if (line == "[C_CountDown]")         readInt(iss, C_CountDown);

                else if (line == "[highStarResolution]")  readBool(iss, line, C_StarsHigh);
                else if (line == "[starField]")           readInt(iss, C_StarField);
                
                //  post fx
                else if (line == "[shaders]")             readBool(iss, line, C_shaders);
                else if (line == "[postFXflashes]")       readBool(iss, line, C_Flashes);
                //  screen
                else if (line == "[resolutionX]")         readInt(iss, C_resX);
                else if (line == "[resolutionY]")         readInt(iss, C_resY);
                else if (line == "[colorDepth]")          readInt(iss, C_colorDepth);
                //  keys
                else if (line == "[screenShotKey]")       iss >> C_screenShotKey;
                else if (line == "[statisticsKey]")       iss >> C_statisticsKey;
                else if (line == "[screenShotFormat]")    iss >> C_screenShotFormat;
                //  audio
                else if (line == "[audioRandom]")         readBool(iss, line, C_audioRandom);
                else if (line == "[audioNextKey]")        iss >> C_audioNextKey;
                else if (line == "[audioPreviousKey]")    iss >> C_audioPreviousKey;
                //  weapons  above
                //  map
                else if (line == "[MapXsize]")            iss >> C_MapXsize;
                else if (line == "[MapYsize]")            iss >> C_MapYsize;
                else if (line == "[MapMinPlanets]")       iss >> C_MapMinPlanets;
                else if (line == "[MapMaxPlanets]")       iss >> C_MapMaxPlanets;
                else if (line == "[MapMinPlanetsSize]")   iss >> C_MapMinPlanetsSize;
                else if (line == "[MapMaxPlanetsSize]")   iss >> C_MapMaxPlanetsSize;
                else if (line == "[MapMinPlanetGap]")     iss >> C_MapMinPlanetGap;

                else if (line == "[MapHomeRadius]")       iss >> C_MapHomeRadius;
                else if (line == "[ShipRadius]")          iss >> C_ShipRadius;
                else if (line == "[BallRadius]")          iss >> C_BallRadius;

                else if (line == "[CyclicBorderX]")       readBool(iss, line, C_CyclicBorderX);
                else if (line == "[CyclicBorderY]")       readBool(iss, line, C_CyclicBorderY);
                else if (line == "[GravityScale]")        iss >> C_GravityScale;
                //  game
                else if (line == "[ShipTurnSpeed]")       iss >> C_ShipTurnSpeed;
                else if (line == "[DamageScale]")         iss >> C_DamageScale;
                else if (line == "[Regeneration]")        iss >> C_Regeneration;
                else if (line == "[FuelRegen]")           iss >> C_FuelRegen;
                else if (line == "[RespawnDelay]")        iss >> C_RespawnDelay;
                else if (line == "[GlowAlpha]")           iss >> C_GlowAlpha;
                else
                    cout << line << " is a bad option in " << C_configPath << "mars.cfg!\n";
            }
        }else 
            if (save())
                cout << "Created " << C_configPath << "mars.cfg, using default settings.\n";

        return true;
    }
}
