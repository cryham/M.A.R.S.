#pragma once

#include "System/Vector2f.hpp"
#include "defines.hpp"
#include "System/settings.hpp"

#include <SFML/Audio.hpp>


/// A namespace for playing sound effects.
/// It is possible to choose which sound to play,
/// it's volume and where to play it (for stereo effects).

namespace sound 
{
    /// All different sound effects.

    enum SoundType
    {
        Pump, Laser, BallExplode, ShipExplode, ShipCollide,  BallPlanetCollide,
        Particle, ShipBallCollide, BallRespawn, PlanetExplode, PumpShipCollide,
        ShipPlanetCollide, ShipRespawn, BlubPop, Fuel, LaserCollide, NoFuel,
        Sniper, Blub, BlubCollide, SniperShipCollide, SniperPlanetCollide, Click,
        Tab, Check, Countdown, Start, Swish, Score,
        COUNT //  amount of entries
    };

    /// Plays a sound file.
    /// \param type specifies the sound::SoundType
    /// \param position selects the location on the screen, where the sound should be played
    /// \param sets the volume
    void playSound (SoundType type, Vector2f const& position = Vector2f(settings::iMapXsize*0.5f, 0), float volume = 100.f);
}
