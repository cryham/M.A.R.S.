#pragma once


/// A namespace for the commentator of the game.
/// The different moods which can be given to the
/// commentator will lead to different sayings.

namespace announcer 
{
    /// Several categories of sayings of the commentator.
    /// For each there are a lot of soundfiles which will
    /// be chosen randomly.
    enum SoundMood
    {
        Affronting, Praising, Neutral,
        COUNT ///< COUNT contains the amount of entries in the enum. Keep it the last!
    };

    /// Updates the announcer.
    /// On slow motion it's pitch is changed.
    void update();

    /// Plays a soundfile based on the given mood.
    /// For each mood there are a lot of soundfiles
    /// which will be chosen randomly.
    void announce (SoundMood mood);
}
