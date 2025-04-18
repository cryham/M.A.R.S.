#pragma once

#include "System/Vector2f.hpp"

#include <SFML/Graphics.hpp>


/// A namespace for post processing shaders.

namespace postFX 
{
    /// Updates the internal bumpmap GLSL shader.
    /// It will not do so, when settings::C_shaders is set to false.
    void update();

    /// Notifies the shader of explosions.
    /// For flash effects.
    void onExplosion();

    /// Returns a pointer to the active shader.
    /// If an error occured, it will return nullptr.
    sf::Shader* get();

    /// Checks, whether GLSL shaders are supported on the current hardware.
    bool supported();

    /// Loads and compiles the post processing shader.
    /// Has to be called once at the beginnig of the program.
    void load();
}
