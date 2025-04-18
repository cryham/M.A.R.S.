#pragma once

#include <SFML/Graphics.hpp>

/// A namespace handling time.
/// The entire game is timed by this namespace.

namespace timer 
{
    /// Updates the timer.
    /// Has to be called every frame once.
    void update(float frameTime);

    /// Notifies the timer when a ship exploded, for slow motion managing.
    void onShipExplode();

    /// Returns the duration of the last frame in seconds. Modified by slow motion effects.
    float frameTime();

    /// Returns the total duration of the game in seconds.  Modified by slow motion effects.
    float totalTime();

    /// Returns the duration of the last frame in seconds. Not affected by slow motion effects.
    float realFrameTime();

    /// Returns the total duration of the game in seconds.  Not affected by slow motion effects.
    float realTotalTime();

    /// Returns the remaining Slow-Mo-time.
    float slowMoTime();

    void resetSlowMotion();

    /// Returns the current frames per second.
    /// Calculated twice a second.
    float fps();
}

