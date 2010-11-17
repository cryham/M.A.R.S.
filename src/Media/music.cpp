/* music.cpp

Copyright (c) 2010 by Felix Lauer and Simon Schneegans

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

# include "Media/music.hpp"

# include "System/settings.hpp"
# include "System/timer.hpp"

namespace music {

    namespace {
        enum MusicType {Technodog, Midnightride, Dancezone, Thisistheday};
        // for Music there is only one channel... who wants to have multiple music files played at once?
        sf::Music musicChannel_;
        bool      initialized_(false);

        void init() {
            musicChannel_.SetRelativeToListener(true);
            sf::Listener::SetPosition(640.f, 0.f, 300.f);
            setGlobalVolume();
            initialized_ = true;
        }

        void playMusic(MusicType music) {
            if (!initialized_) init();
            switch (music) {
                case Technodog:        musicChannel_.OpenFromFile("data/audio/music/technodog.ogg");      break;
                case Thisistheday:     musicChannel_.OpenFromFile("data/audio/music/thisistheday.ogg");   break;
                case Midnightride:     musicChannel_.OpenFromFile("data/audio/music/midnightride.ogg");   break;
                case Dancezone:        musicChannel_.OpenFromFile("data/audio/music/dancezone.ogg");      break;
            }
            musicChannel_.Play();
        }
    }

    void update() {
        if (musicChannel_.GetStatus() == sf::Music::Stopped)
            playMusic(static_cast<MusicType>(sf::Randomizer::Random(0, Thisistheday-1)));

        float slowMoTime(timer::slowMoTime());
        if (slowMoTime > 0.75f) {
            musicChannel_.SetPitch(slowMoTime*0.666f);
        }
        else if (slowMoTime > 0.25f) {
            musicChannel_.SetPitch(0.5f);
        }
        else if (slowMoTime > 0.0f) {
            musicChannel_.SetPitch(1.f-slowMoTime*2.f);
        }
        else musicChannel_.SetPitch(1.f);
    }

    void playMenuMusic() {
        musicChannel_.SetLoop(true);
        playMusic(Thisistheday);
    }

    void playGameMusic() {
        musicChannel_.SetLoop(false);
        playMusic(static_cast<MusicType>(sf::Randomizer::Random(0, Thisistheday-1)));
    }

    void setGlobalVolume() {
        musicChannel_.SetVolume(static_cast<float>(settings::C_musicVolume));
    }
}
