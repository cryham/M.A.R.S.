/* settings.cpp

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

# include "System/settings.hpp"

# include <fstream>
# include <sstream>
# include <iostream>

inline int clamp(int x, int min, int max) {
    return x < min ? min : (x > max ? max : x);
}

namespace settings {

    // game settings ------ adjustable via options menu
    int         C_soundVolume =             30;
    int         C_announcerVolume =         80;
    int         C_musicVolume =             60;
    bool        C_showFPS =                 false;
    bool        C_showParticleCount =       false;
    bool        C_showLatency =             false;
    bool        C_fullScreen =              false;
    bool        C_vsync =                   true;
    bool        C_drawAIPath =              false;
    bool        C_adaptiveParticleCount =   false;
    int         C_globalParticleCount =     50;
    int         C_globalParticleLifeTime =  50;
    bool        C_showStars =               true;
    bool        C_enableSlowMotion =        true;
    bool        C_drawLocalNames =          true;
    bool        C_drawRemoteNames =         true;
    bool        C_drawBotNames =            true;
    bool        C_drawBotOrientation =      false;
    bool        C_drawZones =               false;
    int         C_botsLeft =                4;
    int         C_botsRight =               4;
    int         C_botsDeath =               10;
    int         C_pointLimit =              5;
    int         C_pointLimitDM =            50;
    int         C_pointLimitTDM =           100;
    bool        C_showInfoHide =            true;
    bool        C_showInfoSB =              true;
    bool        C_showInfoDM =              true;
    bool        C_showInfoTDM =             true;
    bool        C_showInfoCK =              true;

    // player settings ----- adjustable via options menu
    std::string   C_playerIName =           "PlayerI";
    Color3f       C_playerIColor =          Color3f(1,0.3,0.3);
    sf::Key::Code C_playerIup =             sf::Key::Up;
    sf::Key::Code C_playerIleft =           sf::Key::Left;
    sf::Key::Code C_playerIright =          sf::Key::Right;
    sf::Key::Code C_playerIfire =           sf::Key::RControl;
    bool          C_playerIteamL =          false;
    bool          C_playerIteamR =          true;
    int           C_playerIShip =           1;
    std::string   C_playerIIName =          "PlayerII";
    Color3f       C_playerIIColor =         Color3f(0.45,0.45,1);
    sf::Key::Code C_playerIIup =            sf::Key::W;
    sf::Key::Code C_playerIIleft =          sf::Key::A;
    sf::Key::Code C_playerIIright =         sf::Key::D;
    sf::Key::Code C_playerIIfire =          sf::Key::LShift;
    bool          C_playerIIteamL =         true;
    bool          C_playerIIteamR =         false;
    int           C_playerIIShip =          1;
    bool          C_networkPlayerI =        true;

    // network settings ----- adjustable via options menu
    std::string C_ip =                      "192.168.0.1";
    std::string C_port =                    "12345";

    void save() {
        std::ofstream outStream("mars.cfg");

        outStream << "// mars config file" << std::endl;
        outStream << "// all these options can be changed with the in-game menu, too." << std::endl << std::endl;

        outStream << "[soundVolume] "           <<  C_soundVolume << std::endl;
        outStream << "[announcerVolume] "       <<  C_announcerVolume << std::endl;
        outStream << "[musicVolume] "           <<  C_musicVolume << std::endl;
        outStream << "[globalParticleCount] "   <<  C_globalParticleCount << std::endl;
        outStream << "[globalParticleLifeTime] "<<  C_globalParticleLifeTime << std::endl;
        outStream << "[showStars] "             << (C_showStars ? "true" : "false") << std::endl;
        outStream << "[showFPS] "               << (C_showFPS ? "true" : "false") << std::endl;
        outStream << "[showParticleCount] "     << (C_showParticleCount ? "true" : "false") << std::endl;
        outStream << "[showLatency] "           << (C_showLatency ? "true" : "false") << std::endl;
        outStream << "[fullScreen] "            << (C_fullScreen ? "true" : "false") << std::endl;
        outStream << "[vsync] "                 << (C_vsync ? "true" : "false") << std::endl;
        outStream << "[drawAIPath] "            << (C_drawAIPath ? "true" : "false") << std::endl;
        outStream << "[adaptiveParticleCount] " << (C_adaptiveParticleCount ? "true" : "false") << std::endl;
        outStream << "[enableSlowMotion] "      << (C_enableSlowMotion ? "true" : "false") << std::endl;
        outStream << "[drawLocalNames] "        << (C_drawLocalNames ? "true" : "false") << std::endl;
        outStream << "[drawRemoteNames] "       << (C_drawRemoteNames ? "true" : "false") << std::endl;
        outStream << "[drawBotNames] "          << (C_drawBotNames ? "true" : "false") << std::endl;
        outStream << "[drawBotOrientation] "    << (C_drawBotOrientation ? "true" : "false") << std::endl;
        outStream << "[drawZones] "             << (C_drawZones ? "true" : "false") << std::endl;
        outStream << "[botsLeft] "              << C_botsLeft << std::endl;
        outStream << "[botsRight] "             << C_botsRight << std::endl;
        outStream << "[botsDeath] "             << C_botsDeath << std::endl;
        outStream << "[pointLimit] "            << C_pointLimit << std::endl;
        outStream << "[pointLimitDM] "          << C_pointLimitDM << std::endl;
        outStream << "[pointLimitTDM] "         << C_pointLimitTDM << std::endl;
        outStream << "[playerIName] "           <<  C_playerIName << std::endl;
        outStream << "[playerIKeys] "           <<  C_playerIup << " "<< C_playerIright << " " << C_playerIleft << " " << C_playerIfire << std::endl;
        outStream << "[playerIColor] "          <<  C_playerIColor.r() << " "<< C_playerIColor.g() << " " << C_playerIColor.b() << std::endl;
        outStream << "[playerITeamL] "          << (C_playerIteamL ? "true" : "false") << std::endl;
        outStream << "[playerITeamR] "          << (C_playerIteamR ? "true" : "false") << std::endl;
        outStream << "[playerIShip] "           <<  C_playerIShip << std::endl;
        outStream << "[playerIIName] "          <<  C_playerIIName << std::endl;
        outStream << "[playerIIKeys] "          <<  C_playerIIup << " "<< C_playerIIright << " " << C_playerIIleft << " " << C_playerIIfire << std::endl;
        outStream << "[playerIIColor] "         <<  C_playerIIColor.r() << " "<< C_playerIIColor.g() << " " << C_playerIIColor.b() << std::endl;
        outStream << "[playerIITeamL] "         << (C_playerIIteamL ? "true" : "false") << std::endl;
        outStream << "[playerIITeamR] "         << (C_playerIIteamR ? "true" : "false") << std::endl;
        outStream << "[playerIIShip] "          <<  C_playerIIShip << std::endl;
        outStream << "[connectIP] "             <<  C_ip << std::endl;
        outStream << "[connectPort] "           <<  C_port << std::endl;
        outStream << "[networkTeamRed] "        << (C_networkPlayerI ? "true" : "false") << std::endl;
        outStream << "[showInfoHide] "          << (C_showInfoHide ? "true" : "false") << std::endl;
        outStream << "[showInfoSB] "            << (C_showInfoSB ? "true" : "false") << std::endl;
        outStream << "[showInfoDM] "            << (C_showInfoDM ? "true" : "false") << std::endl;
        outStream << "[showInfoTDM] "           << (C_showInfoTDM ? "true" : "false") << std::endl;
        outStream << "[showInfoCK] "            << (C_showInfoCK ? "true" : "false") << std::endl;

        outStream.close();
    }

    void load() {
        std::ifstream inStream("mars.cfg");
        char line[1024];

        if (inStream.good()) {
            while(inStream.getline(line, 1024)) {
                std::string inputLine (line);

                while (inputLine[0] == ' ')
                    inputLine.erase(inputLine.begin());
                while (inputLine[inputLine.size()-2] == ' ')
                    inputLine.erase(inputLine.size()-2);

                // ignore comments and empty lines
                if(inputLine.size() == 2 || (inputLine.size() > 2 && (inputLine[0] != '/' && inputLine[1] != '/'))) {
                    std::istringstream iss (line);
                    std::string inputLine;
                    iss >> inputLine;
                    if      (inputLine == "[soundVolume]") {
                        int value;
                        iss >> value;
                        C_soundVolume = clamp(value, 0, 100);
                    }
                    else if (inputLine == "[announcerVolume]") {
                        int value;
                        iss >> value;
                        C_announcerVolume = clamp(value, 0, 100);
                    }
                    else if (inputLine == "[musicVolume]") {
                        int value;
                        iss >> value;
                        C_musicVolume = clamp(value, 0, 100);
                    }
                    else if (inputLine == "[globalParticleCount]") {
                        int value;
                        iss >> value;
                        C_globalParticleCount = clamp(value, 10, 300);
                    }
                    else if (inputLine == "[globalParticleLifeTime]") {
                        int value;
                        iss >> value;
                        C_globalParticleLifeTime = clamp(value, 10, 300);
                    }
                    else if (inputLine == "[showStars]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showStars = true;
                        else if (value == "false")  C_showStars = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showFPS]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showFPS = true;
                        else if (value == "false")  C_showFPS = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showParticleCount]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showParticleCount = true;
                        else if (value == "false")  C_showParticleCount = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showLatency]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showLatency = true;
                        else if (value == "false")  C_showLatency = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[fullScreen]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_fullScreen = true;
                        else if (value == "false")  C_fullScreen = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[vsync]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_vsync = true;
                        else if (value == "false")  C_vsync = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawAIPath]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawAIPath = true;
                        else if (value == "false")  C_drawAIPath = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[adaptiveParticleCount]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_adaptiveParticleCount = true;
                        else if (value == "false")  C_adaptiveParticleCount = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[enableSlowMotion]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_enableSlowMotion = true;
                        else if (value == "false")  C_enableSlowMotion = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawLocalNames]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawLocalNames = true;
                        else if (value == "false")  C_drawLocalNames = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawRemoteNames]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawRemoteNames = true;
                        else if (value == "false")  C_drawRemoteNames = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawBotNames]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawBotNames = true;
                        else if (value == "false")  C_drawBotNames = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawBotOrientation]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawBotOrientation = true;
                        else if (value == "false")  C_drawBotOrientation = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[drawZones]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_drawZones = true;
                        else if (value == "false")  C_drawZones = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[botsLeft]") {
                        int value;
                        iss >> value;
                        C_botsLeft = clamp(value, 0, 20);
                    }
                    else if (inputLine == "[botsRight]") {
                        int value;
                        iss >> value;
                        C_botsRight = clamp(value, 0, 20);
                    }
                    else if (inputLine == "[botsDeath]") {
                        int value;
                        iss >> value;
                        C_botsDeath = clamp(value, 0, 150);
                    }
                    else if (inputLine == "[pointLimit]") {
                        int value;
                        iss >> value;
                        C_pointLimit = clamp(value, 1, 20);
                    }
                    else if (inputLine == "[pointLimitDM]") {
                        int value;
                        iss >> value;
                        C_pointLimitDM = clamp(value, 1, 200);
                    }
                    else if (inputLine == "[pointLimitTDM]") {
                        int value;
                        iss >> value;
                        C_pointLimitTDM = clamp(value, 1, 500);
                    }
                    else if (inputLine == "[playerIName]") {
                        std::string value;
                        iss >> value;
                        C_playerIName.assign(value, 0, 12);
                    }
                    else if (inputLine == "[playerIIName]") {
                        std::string value;
                        iss >> value;
                        C_playerIIName.assign(value, 0, 12);
                    }
                    else if (inputLine == "[playerIKeys]") {
                        int temp;
                        iss >> temp;
                        C_playerIup = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIright = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIleft = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIfire = (sf::Key::Code)temp;
                    }
                    else if (inputLine == "[playerIIKeys]") {
                        int temp;
                        iss >> temp;
                        C_playerIIup = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIIright = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIIleft = (sf::Key::Code)temp;
                        iss >> temp;
                        C_playerIIfire = (sf::Key::Code)temp;
                    }
                    else if (inputLine == "[playerIColor]") {
                        float r, g, b;
                        iss >> r;
                        iss >> g;
                        iss >> b;
                        C_playerIColor = Color3f(r,g,b);
                    }
                    else if (inputLine == "[playerIIColor]") {
                        float r, g, b;
                        iss >> r;
                        iss >> g;
                        iss >> b;
                        C_playerIIColor = Color3f(r,g,b);
                    }
                    else if (inputLine == "[playerITeamL]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_playerIteamL = true;
                        else if (value == "false")  C_playerIteamL = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[playerITeamR]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_playerIteamR = true;
                        else if (value == "false")  C_playerIteamR = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[playerIShip]") {
                        iss >> C_playerIShip;
                    }
                    else if (inputLine == "[playerIIShip]") {
                        iss >> C_playerIIShip;
                    }
                    else if (inputLine == "[playerIITeamL]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_playerIIteamL = true;
                        else if (value == "false")  C_playerIIteamL = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[playerIITeamR]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_playerIIteamR = true;
                        else if (value == "false")  C_playerIIteamR = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[connectIP]") {
                        iss >> C_ip;
                    }
                    else if (inputLine == "[connectPort]") {
                        iss >> C_port;
                    }
                    else if (inputLine == "[networkTeamRed]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_networkPlayerI = true;
                        else if (value == "false")  C_networkPlayerI = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showInfoHide]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showInfoHide = true;
                        else if (value == "false")  C_showInfoHide = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showInfoSB]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showInfoSB = true;
                        else if (value == "false")  C_showInfoSB = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showInfoDM]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showInfoDM = true;
                        else if (value == "false")  C_showInfoDM = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showInfoTDM]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showInfoTDM = true;
                        else if (value == "false")  C_showInfoTDM = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else if (inputLine == "[showInfoCK]") {
                        std::string value;
                        iss >> value;
                        if (value == "true")        C_showInfoCK = true;
                        else if (value == "false")  C_showInfoCK = false;
                        else std::cout << value << " is a bad value for " << inputLine << ". Use true or false instead.\n";
                    }
                    else
                        std::cout << inputLine << " is a bad option in mars.cfg!\n";
                }
            }
        }
        else {
            std::cout << "Could not find mars.cfg! Using default settings...\n";
        }
        inStream.close();
    }
}
