#pragma once

#include "Color3f.hpp"
#include "Weapons/Weapon.hpp"
#include "Specials/Special.hpp"
#include "System/Key.hpp"
#include "Weapons/weapons.hpp"

#include <SFML/Graphics.hpp>
#include <string>


/// A namespace which handles the settings.
/// All settings are stored in global variables and
/// can be saved to and loaded from file

namespace settings
{
    /// Loads all settings from the file.
    /// All settings are stored in the file mars.cfg in C_configPath.
    /// This has to be called once at the beginning of the game. If an error
    /// occurs, default settings are used.
    bool load();

    /// Saves the current state of the variables to file.
    bool save();

    /// \name Game settings
    ///@{
    extern int            iSoundVolume;
    extern int            iAnnouncerVolume;
    extern int            iMusicVolume;
    
    extern bool           bShowFPS;
    extern bool           bShowParticleCount;

    extern bool           bFullScreen;
    extern bool           bVSync;

    extern bool           bStarsHigh;
    extern int            iStarField;
    extern int            iParticleCount;
    extern bool           bAdaptiveParticleCount;
    extern int            iParticleLifeTime;

    extern int            iBotsLeft;
    extern int            iBotsRight;
    extern int            iBotsDeath;
    extern int            iPointLimitSB;
    extern int            iPointLimitCK;
    extern int            iPointLimitDM;
    extern int            iPointLimitTDM;

    extern int            iPowerUpRate;
    extern int            iSlowMoKickIn;
    extern int            iGameSpeed;

    extern bool           bShowInfoHide;
    extern bool           bShowInfoSB;
    extern bool           bShowInfoDM;
    extern bool           bShowInfoTDM;
    extern bool           bShowInfoCK;

    extern bool           bShowSelectLanguage;
    extern int            iLanguageID;

    extern bool           bShowToolTips;
    extern bool           bNoConfirmations;
    // extern int         iUIscale;  UiElement::scale_
    extern bool           bLogoSigns;
    extern int            iCountDown;

    extern int            iResX;
    extern int            iResY;
    extern int            iColorDepth;
    extern int            iAntiAliasing;

    extern bool           bShaders;
    extern bool           bFlashes;
    extern Key            keyScreenShot;

    extern bool           bAudioRandom;
    extern Key            keyAudioNext;
    extern Key            keyAudioPrev;

    extern Key            keyStatistics;
    extern std::string    sConfigPath;
    extern std::string    sDataPath;
    extern std::string    sScreenShotFormat;
    
    extern bool           bEnabledWeapons[weapons::All];
    extern bool           bEnabledWeaponsByUser[weapons::All];
    extern bool           bEnabledSpecials[specials::All];
    extern bool           bEnabledSpecialsByUser[specials::All];
    ///@}

    /// \name Map settings new
    ///@{
    extern int            iMapMinPlanets;
    extern int            iMapMaxPlanets;
    extern int            iMapMinPlanetsSize;
    extern int            iMapMaxPlanetsSize;
    
    extern int            iMapBlackHoles;
    extern int            iMapSuns;

    extern int            iMapMinPlanetGap;
    extern int            iMapHomeRadius;

    extern int            iMapXsize;
    extern int            iMapYsize;
    // extern int         iMapYaspect;

    extern int            iShipRadius;
    extern int            iBallRadius;
    ///@}

    /// \name Game settings new
    ///@{
    extern int            iDamageScale;
    extern int            iRegeneration;
    extern int            iFuelRegen;
    extern int            iRespawnDelay;
    
    extern int            iShipTurnSpeed;
    extern int            iGlowAlpha;
    extern int            iAimRayAlpha;

    extern bool           bCyclicBorderX;
    extern bool           bCyclicBorderY;
    extern int            iGravityScale;
    ///@}

    /// \name Turrets new
    extern int            iTurretsInSpace;
    extern int            iTurretsOnHome;
    extern int            iTurretsOnPlanet;
    extern int            iTurretAttackSpeed;
    extern int            iTurretRespawnDelay;
    extern int            iTurretTurnSpeed;
    ///@}


    /// \name Player settings
    ///@{
    extern sf::String     sPlayer1Name;
    extern Color3f        clr1Player;
    extern Color3f        clr1Team;
    
    extern Key            key1up;
    extern Key            key1down;
    extern Key            key1boost;

    extern Key            key1left;
    extern Key            key1right;
    
    extern Key            key1fire;
    extern Key            key1SpecialKey;
    extern Key            key1prev;
    extern Key            key1next;

    extern bool           bPlayer1teamL;
    extern bool           bPlayer1teamR;
    extern bool           bPlayer1mouseAim;

    extern int            iPlayer1Ship;
    extern weapons::WeaponType   player1Weapon;
    extern specials::SpecialType player1Special;

    extern sf::String     sPlayer2Name;
    extern Color3f        clr2Player;
    extern Color3f        clr2Team;
    
    extern Key            key2up;
    extern Key            key2down;
    extern Key            key2boost;

    extern Key            key2left;
    extern Key            key2right;
    
    extern Key            key2fire;
    extern Key            key2SpecialKey;
    extern Key            key2prev;
    extern Key            key2next;

    extern bool           bPlayer2teamL;
    extern bool           bPlayer2teamR;
    extern bool           bPlayer2mouseAim;

    extern int            iPlayer2Ship;
    extern weapons::WeaponType   player2Weapon;
    extern specials::SpecialType player2Special;
    ///@}

    /// \name AI settings
    ///@{
    extern int            iBotsDifficulty;
    extern bool           bDrawBotJobs;
    extern bool           bDrawAIPath;
    extern bool           bDrawZones;
    ///@}

    /// \name Network settings unused
    ///@{
    // extern sf::String     sIP;
    // extern sf::String     sPort;
    // extern bool           bNetworkPlayerI;
    // extern bool           bShowLatency;
    ///@}
};
