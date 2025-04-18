#pragma once

#include "System/Vector2f.hpp"

#include <SFML/System.hpp>

namespace toolTip 
{

    void draw();

    void mouseMoved(Vector2f const& position);

    void show(const sf::String& text);
}


