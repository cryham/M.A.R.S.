#pragma once

#include <SFML/Audio.hpp>


/// A namespace for playing music.
/// Music is streamed from OGG files.

namespace music 
{
    /// Updates the music player.
    /// If the ingame music has stopped, a new randomly
    /// chosen track will be played.
    void update();

    /// Plays a music file.
    void play(std::string fileName);
    /// Plays a random music file.
    void play();
    /// Switches to the next track.
    void next();
    /// Switches to the previous track.
    void previous();
    /// Stops playing Music.
    void stop();

    /// Silences the music slowly.
    void fadeOut();

    /// Applies the global music Volume.
    /// Which is set in \a settings::C_musicVolume. This is useful
    /// when this variable has been changed to apply the effect.
    void setGlobalVolume();
}
