/* OptionsMenu.cpp

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

#include "Menu/OptionsMenu.hpp"

#include "Media/text.hpp"
#include "Interface/UiWindow.hpp"
#include "Interface/Button.hpp"
#include "Interface/Slider.hpp"
#include "Interface/Checkbox.hpp"
#include "Interface/Tab.hpp"
#include "Interface/TabList.hpp"
#include "Interface/KeyEdit.hpp"
#include "Interface/TextEdit.hpp"
#include "Interface/ShipPreview.hpp"
#include "Interface/Line.hpp"
#include "Interface/RadioGroup.hpp"
#include "Interface/RadioButton.hpp"
#include "Interface/ComboBox.hpp"
#include "Interface/LanguageButton.hpp"
#include "Interface/ColorPicker.hpp"
#include "Interface/LabeledBox.hpp"
#include "System/window.hpp"
#include "System/settings.hpp"
#include "Menu/menus.hpp"
#include "System/generateName.hpp"
#include "Media/music.hpp"
#include "Particles/Star.hpp"
#include "Media/sound.hpp"
#include "Locales/locales.hpp"
#include "Menu/ChooseLanguage.hpp"
#include "Menu/ShaderError.hpp"
#include "Menu/About.hpp"
#include "Menu/Connect.hpp"
#include "Menu/InfoCK.hpp"
#include "Menu/InfoSB.hpp"
#include "Menu/InfoDM.hpp"
#include "Menu/InfoTDM.hpp"
#include "Menu/InfoHide.hpp"
#include "Shaders/postFX.hpp"
#include "defines.hpp"

#include <SFML/Window.hpp>
#include <sstream>


UiWindow* OptionsMenu::instance_(NULL);
bool OptionsMenu::kOk_(false);
bool OptionsMenu::fullscreen_(false);
bool OptionsMenu::vsync_(false);
bool OptionsMenu::shaders_(false);
int OptionsMenu::starfield_(0);
sf::String OptionsMenu::resolution_("");
sf::String OptionsMenu::colorDepth_("");
sf::String OptionsMenu::format_("");
int  OptionsMenu::soundVolume_(0);
int  OptionsMenu::musicVolume_(0);
int  OptionsMenu::announcerVolume_(0);


UiWindow* OptionsMenu::get()
{
    if (instance_ == NULL)
    {
        instance_ = new OptionsMenu(700, 430);

        instance_->addWidget(new Button(locales::getLocale(locales::Ok), NULL, &kOk_,
            Vector2f(500,360), 90, 20));
        instance_->addWidget(new Label(locales::getLocale(locales::Options), TEXT_ALIGN_LEFT,
            Vector2f(10,10), 20.f, getColor3f(0.5f, 0.9f, 1.f), false));

        TabList* tabList  = new TabList(Vector2f(10,55), 580, 270);
        Tab* tabInterface = new Tab(locales::getLocale(locales::Interface), 90);
        Tab* tabGameplay  = new Tab(locales::getLocale(locales::Gameplay), 90);
        Tab* tabGraphics  = new Tab(locales::getLocale(locales::Display), 80);
        Tab* tabAudio     = new Tab(locales::getLocale(locales::Audio), 80);
        Tab* tabPlayer1   = new Tab(&settings::C_playerIName, 100);
        Tab* tabPlayer2   = new Tab(&settings::C_playerIIName, 100);

        //  Interface GUI
        int y = 30, yadd = 20;
        tabInterface->addWidget(new LabeledBox(locales::getLocale(locales::GeneralOptions),
            Vector2f(10, y), 560, 110));  y += yadd*3/2;
        tabInterface->addWidget(new LanguageButton(locales::getLocale(locales::Language),
            Vector2f(20, y), 540, 240));  y += yadd*3/2;

        tabInterface->addWidget(new Slider(locales::Scale, locales::ttScale,
            &settings::C_globalParticleCount, 1, 300, 15,
            Vector2f(20,y), 540, 240, true));  y += yadd;
        tabInterface->addWidget(new Checkbox(locales::NoConfirmations, locales::ttNoConfirmations,
            &settings::C_noConfirmations,
            Vector2f(20,y), 140));  y += yadd;

        std::vector<sf::String> fileFormats;
            fileFormats.push_back("BITMAP (*.bmp)");
            fileFormats.push_back("GIF (*.gif)");
            fileFormats.push_back("JPEG (*.jpg)");
            fileFormats.push_back("PNG(*.png)");
            fileFormats.push_back("TARGA (*.tga)");
        tabInterface->addWidget(new ComboBox(locales::getLocale(locales::ScreenShotFormat), locales::getLocale(locales::ttScreenShotFormat),
            &format_, fileFormats,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabInterface->addWidget(new KeyEdit(locales::getLocale(locales::ScreenShotKey), locales::getLocale(locales::ttScreenShotKey),
            &settings::C_screenShotKey,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabInterface->addWidget(new KeyEdit(locales::getLocale(locales::StatisticsKey), locales::getLocale(locales::ttStatisticsKey),
            &settings::C_statisticsKey,
            Vector2f(20,y), 540, 240));  y += yadd*2;

        tabInterface->addWidget(new LabeledBox(locales::getLocale(locales::GameInformation),
            Vector2f(10, y), 560, 90));  y += yadd*3/2;
        tabInterface->addWidget(new Checkbox(locales::FramesPerSecond, locales::ttFramesPerSecond,
            &settings::C_showFPS,
            Vector2f(20,y), 140));  y += yadd;
        tabInterface->addWidget(new Checkbox(locales::ParticleCount, locales::ttParticleCount,
            &settings::C_showParticleCount,
            Vector2f(20,y), 140));  y += yadd;
        tabInterface->addWidget(new Checkbox(locales::ShowToolTips, locales::ttShowToolTips,
            &settings::C_showToolTips,
            Vector2f(20,y), 140));  y += yadd*3/2;
       
        //  Graphics
        y = 30;
        tabGraphics->addWidget(new LabeledBox(locales::getLocale(locales::WindowSettings),
            Vector2f(10, y), 560, 110));  y += yadd*3/2;
        tabGraphics->addWidget(new Checkbox(locales::Fullscreen, locales::ttFullscreen,
            &fullscreen_,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Checkbox(locales::VerticalSynchronisation, locales::ttVerticalSynchronisation,
            &vsync_,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Checkbox(locales::Shaders, locales::ttShaders,
            &shaders_,
            Vector2f(20,y), 150));  y += yadd;
        
        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        std::vector<sf::String> resolutions;
        std::vector<sf::String> colorDepths;
        for (auto& it : modes)
        {
            if (it.width >= 800 && it.bitsPerPixel >= 8)
            {
                std::stringstream res, depth;
                res << it.width << " x " << it.height;
                depth << it.bitsPerPixel;
                sf::String resString(res.str()), depthString(depth.str());

                bool newDepth(true), newRes(true);
                for (auto& it : resolutions)
                    if (it == resString)
                        newRes = false;
                for (auto& it : colorDepths)
                    if (it == depthString) newDepth = false;
                
                if (newRes)
                    resolutions.push_back(res.str());
                if (newDepth)
                    colorDepths.push_back(depth.str());
            }
        }
        std::vector<sf::String> off;
        off.push_back(*locales::getLocale(locales::SlowMoOff));

        tabGraphics->addWidget(new ComboBox(locales::getLocale(locales::Resolution), locales::getLocale(locales::ttResolution),
            &resolution_, resolutions,
            Vector2f(20,y), 540, 240));  y += yadd;
        
        tabGraphics->addWidget(new LabeledBox(locales::getLocale(locales::GameSettings),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabGraphics->addWidget(new Checkbox(locales::StarsHigh, locales::ttStarsHigh,
            &settings::C_StarsHigh,
            Vector2f(20,y), 150));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::StarField, locales::ttStarField,
            &starfield_, 0, 20000, 1000,
            Vector2f(20,y), 540, 240, true, off));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::ParticleCountSlider, locales::ttParticleCountSlider,
            &settings::C_globalParticleCount, 1, 300, 15,
            Vector2f(20,y), 540, 240, true));  y += yadd;
        tabGraphics->addWidget(new Slider(locales::ParticleLifetime, locales::ttParticleLifetime,
            &settings::C_globalParticleLifeTime, 1, 300, 15,
            Vector2f(20,y), 540, 240, true));  y += yadd;

        //  Audio
        y = 30.f;
        tabAudio->addWidget(new LabeledBox(locales::getLocale(locales::VolumeSettings),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabAudio->addWidget(new Slider(locales::MusicVolume, locales::ttMusicVolume,
            &musicVolume_, 0, 100, 5,
            Vector2f(20,y), 540, 240, true, off));  y += yadd;
        tabAudio->addWidget(new Slider(locales::SoundVolume, locales::ttSoundVolume,
            &soundVolume_, 0, 100, 5,
            Vector2f(20,y), 540, 240, true, off));  y += yadd;
        tabAudio->addWidget(new Slider(locales::AnnouncerVolume, locales::ttAnnouncerVolume,
            &announcerVolume_, 0, 100, 5,
            Vector2f(20,y), 540, 240, true, off));  y += yadd*2;
        
        tabAudio->addWidget(new LabeledBox(locales::getLocale(locales::PlaybackSettings),
            Vector2f(10,y), 560, 60));  y += yadd*3/2;
        tabAudio->addWidget(new Checkbox(locales::AudioRandom, locales::ttAudioRandom,
            &settings::C_audioRandom,
            Vector2f(20,y), 150));  y += yadd;
        tabAudio->addWidget(new KeyEdit(locales::AudioNextKey, locales::ttAudioNextKey,
            &settings::C_audioNextKey,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabAudio->addWidget(new KeyEdit(locales::AudioPreviousKey, locales::ttAudioPreviousKey,
            &settings::C_audioPreviousKey,
            Vector2f(20,y), 540, 240));  y += yadd;

        //  Gameplay
        y = 30.f;
        tabGameplay->addWidget(new LabeledBox(locales::getLocale(locales::SpecialEffects),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabGameplay->addWidget(new Slider(locales::SlowMoKickIn, locales::ttSlowMoKickIn,
            &settings::C_slowMoKickIn, 0, 10, 1,
            Vector2f(20,y), 540, 240, true, off));  y += yadd;
        tabGameplay->addWidget(new Slider(locales::GameSpeed, locales::ttGameSpeed,
            &settings::C_gameSpeed, 50, 200, 5,
            Vector2f(20,y), 540, 240, true));  y += yadd;
        
        tabGameplay->addWidget(new LabeledBox(locales::getLocale(locales::DebuggingInformation),
            Vector2f(10,y), 560, 90));  y += yadd*3/2;
        tabGameplay->addWidget(new Checkbox(locales::AIJobs, locales::ttBotsOrientation, &settings::C_drawBotJobs,
            Vector2f(20,y), 140));  y += yadd;
        tabGameplay->addWidget(new Checkbox(locales::Zones, locales::ttZones, &settings::C_drawZones,
            Vector2f(20,y), 140));  y += yadd;
        tabGameplay->addWidget(new Checkbox(locales::AIPaths, locales::ttAIPaths, &settings::C_drawAIPath,
            Vector2f(20,y), 140));  y += yadd;


        //  Player I keys
        y = 30.f;
        tabPlayer1->addWidget(new TextEdit(locales::getLocale(locales::Name), &settings::C_playerIName, "PlayerI",
            Vector2f(20,y), 540, 240, TEXT_EDIT, 12));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Accelerate),     NULL, &settings::C_playerIup,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::AccelerateBack), NULL, &settings::C_playerIdown,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Boost),          NULL, &settings::C_playerIboost,
            Vector2f(20,y), 540, 240));  y += yadd;
        
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::TurnLeft),  NULL, &settings::C_playerIleft,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::TurnRight), NULL, &settings::C_playerIright,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::Fire),      NULL, &settings::C_playerIfire,
            Vector2f(20,y), 540, 240));  y += yadd;

        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::SpecialKey),       NULL, &settings::C_playerISpecialKey,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::AudioPreviousKey), NULL, &settings::C_playerIprev,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer1->addWidget(new KeyEdit(locales::getLocale(locales::AudioNextKey),     NULL, &settings::C_playerInext,
            Vector2f(20,y), 540, 240));  y += yadd;

        tabPlayer1->addWidget(new LabeledBox(locales::getLocale(locales::ShipSettings),
            Vector2f(10,y), 560, 90));  y += yadd;
        tabPlayer1->addWidget(new ShipPreview(
            &settings::C_playerIColor, &settings::C_playerITeamColor, &settings::C_playerIShip,
            Vector2f(510,y)));  y += yadd;
        tabPlayer1->addWidget(new Slider(locales::getLocale(locales::ShipName), NULL,
            &settings::C_playerIShip, 0, SHIP_GRAPHICS_COUNT, 1,
            Vector2f(20,y), 410, 240, true, generateName::shipNames()));  y += yadd;
        tabPlayer1->addWidget(new ColorPicker(locales::getLocale(locales::PlayerColor), &settings::C_playerIColor,
            Vector2f(20,y), 410, 240));  y += yadd;
        tabPlayer1->addWidget(new ColorPicker(locales::getLocale(locales::TeamColor), &settings::C_playerITeamColor,
            Vector2f(20,y), 410, 240));  y += yadd;

        //  Player II keys
        y = 30.f;
        tabPlayer2->addWidget(new TextEdit(locales::getLocale(locales::Name), &settings::C_playerIIName, "PlayerII",
            Vector2f(20,y), 540, 240, TEXT_EDIT, 12));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Accelerate),     NULL, &settings::C_playerIIup,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::AccelerateBack), NULL, &settings::C_playerIIdown,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Boost),          NULL, &settings::C_playerIIboost,
            Vector2f(20,y), 540, 240));  y += yadd;
        
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::TurnLeft),  NULL, &settings::C_playerIIleft,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::TurnRight), NULL, &settings::C_playerIIright,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::Fire),      NULL, &settings::C_playerIIfire,
            Vector2f(20,y), 540, 240));  y += yadd;

        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::SpecialKey),       NULL, &settings::C_playerIISpecialKey,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::AudioPreviousKey), NULL, &settings::C_playerIIprev,
            Vector2f(20,y), 540, 240));  y += yadd;
        tabPlayer2->addWidget(new KeyEdit(locales::getLocale(locales::AudioNextKey),     NULL, &settings::C_playerIInext,
            Vector2f(20,y), 540, 240));  y += yadd;

        tabPlayer2->addWidget(new LabeledBox(locales::getLocale(locales::ShipSettings),
            Vector2f(10, y), 560, 90));  y += yadd;
        tabPlayer2->addWidget(new ShipPreview(
            &settings::C_playerIIColor, &settings::C_playerIITeamColor, &settings::C_playerIIShip,
            Vector2f(510,y)));  y += yadd;
        tabPlayer2->addWidget(new Slider(locales::getLocale(locales::ShipName), NULL,
            &settings::C_playerIIShip, 0, SHIP_GRAPHICS_COUNT, 1,
            Vector2f(20,y), 410, 240, true, generateName::shipNames()));  y += yadd;
        tabPlayer2->addWidget(new ColorPicker(locales::getLocale(locales::PlayerColor), &settings::C_playerIIColor,
            Vector2f(20,y), 410, 240));  y += yadd;
        tabPlayer2->addWidget(new ColorPicker(locales::getLocale(locales::TeamColor), &settings::C_playerIITeamColor,
            Vector2f(20,y), 410, 240));  y += yadd;


        tabList->addTab(tabInterface);
        tabList->addTab(tabGraphics);
        tabList->addTab(tabAudio);
        tabList->addTab(tabGameplay);
        tabList->addTab(tabPlayer2);
        tabList->addTab(tabPlayer1);
        instance_->addWidget(tabList);
    }
    return instance_;
}


void OptionsMenu::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;

        int resX, resY, depth;
        std::stringstream sstr1(resolution_);
        sstr1 >> resX;
        char x; sstr1 >> x;
        sstr1 >> resY;

        std::stringstream sstr2(colorDepth_);
        sstr2 >> depth;

        if (resX != settings::C_resX || resY != settings::C_resY ||
            depth != settings::C_colorDepth ||
            fullscreen_ != settings::C_fullScreen || vsync_ != settings::C_vsync ||
            shaders_ != settings::C_shaders)
        {
            settings::C_resX = resX;
            settings::C_resY = resY;
            settings::C_colorDepth = depth;
            settings::C_fullScreen = fullscreen_;
            settings::C_vsync = vsync_;
            settings::C_shaders = shaders_;
            window::create();
        }

        if      (format_ == "BITMAP (*.bmp)") settings::C_screenShotFormat = "bmp";
        else if (format_ == "GIF (*.gif)")    settings::C_screenShotFormat = "gif";
        else if (format_ == "TARGA (*.tga)")  settings::C_screenShotFormat = "tga";
        else if (format_ == "PNG(*.png)")     settings::C_screenShotFormat = "png";
        else if (format_ == "JPEG (*.jpg)")   settings::C_screenShotFormat = "jpg";

        if (starfield_ != settings::C_StarField)
        {
            settings::C_StarField = starfield_;
            if (settings::C_StarField > 0)
                Star::init();
            else
                Star::clear();
        }

        locales::load();
        menus::reload();

        settings::save();
        menus::hideWindow();
    }
    if (shaders_ != settings::C_shaders)
    {
        if (shaders_ && !postFX::supported())
        {
            shaders_ = false;
            settings::C_shaders = false;
            menus::showWindow(ShaderError::get());
        }
    }
    if (soundVolume_ != settings::C_soundVolume)
        settings::C_soundVolume = soundVolume_;

    if (musicVolume_ != settings::C_musicVolume)
    {
        settings::C_musicVolume = musicVolume_;
        music::setGlobalVolume();
    }
    if (announcerVolume_ != settings::C_announcerVolume)
        settings::C_announcerVolume = announcerVolume_;
}


void OptionsMenu::onShow()
{
    fullscreen_      = settings::C_fullScreen;
    vsync_           = settings::C_vsync;
    shaders_         = settings::C_shaders;
    soundVolume_     = settings::C_soundVolume;
    musicVolume_     = settings::C_musicVolume;
    announcerVolume_ = settings::C_announcerVolume;
    starfield_       = settings::C_StarField;

    if      (settings::C_screenShotFormat == "bmp") format_ = "BITMAP (*.bmp)";
    else if (settings::C_screenShotFormat == "gif") format_ = "GIF (*.gif)";
    else if (settings::C_screenShotFormat == "tga") format_ = "TARGA (*.tga)";
    else if (settings::C_screenShotFormat == "png") format_ = "PNG(*.png)";
    else if (settings::C_screenShotFormat == "jpg") format_ = "JPEG (*.jpg)";

    sf::VideoMode mode(settings::C_resX, settings::C_resY);
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    if (modes.size() > 0 && !mode.isValid())
    {
        mode = sf::VideoMode::getFullscreenModes().front();
        settings::C_resX = mode.width;
        settings::C_resY = mode.height;
    }

    std::stringstream sstr1;
    sstr1 << settings::C_resX << " x " << settings::C_resY;
    resolution_ = sstr1.str();

    std::stringstream sstr2;
    sstr2 << settings::C_colorDepth;
    colorDepth_ = sstr2.str();
}

void OptionsMenu::reset()
{
    if (instance_)
        delete instance_;
    instance_ = NULL;
}
