#pragma once

#include "System/Color3f.hpp"

#include <SFML/OpenGL.hpp>


/// A namespace for texture handling.
/// When asked for a reference to a texture, this namespace will load the
/// texture from file. Additionally it stores the overall colors of the
/// planet textures.

namespace texture
{
    ///  All different textures.
    enum TextureType
    {
        Home, Planet1, Planet2, Planet3, Planet4, Planet5,
        Planet6, Planet7, Planet8, Planet9, Planet10,
        Planet11, Planet12, Planet13, Planet14, Planet15,

        Sun1, Sun2, Sun3, Sun4, SunHeat,
        
        Asteroid1, Asteroid2, Asteroid3, Asteroid4, Asteroid5,
        Asteroid6, Asteroid7, Asteroid8, Asteroid9, Asteroid10,
        Asteroid11, Asteroid12,
        
        Ice, Bolt, Cracks, Hole1,
        Ball, Particles, PowerUps, Ships, Weapons,
        // MotherShip, MotherShipPlayerLayer,  // unused
        
        Sign1, Sign2, Logo1,
        Cannon, CannonSocket, Stars1_large,
        Stars1_medium, Stars2_large, Stars2_medium, Star,
        
        EnergyBars, Widgets,
        CountDown4, CountDown3, CountDown2, CountDown1, CountDown0,
        ShockWave, Interface,
        
        COUNT  // amount of entries
    };

    ///  Returns a const& to the texture.
    ///  You can specify which font to return with the \a type parameter.
    GLuint const& getTexture(TextureType type);

    ///  Returns a randomly chosen planet texture.
    TextureType const randomPlanet();

    ///  Returns the overall color of a planet texture.
    Color3f const getMudColor(TextureType planetTexture);
}
