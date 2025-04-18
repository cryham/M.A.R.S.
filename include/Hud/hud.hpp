#pragma once

#include "System/Vector2f.hpp"
#include "System/Color3f.hpp"


namespace hud 
{
    void init();

    void update();
    void draw();
    void drawMessages();

    void displayPoints(bool show = true);
    void displayStats(bool show = true);
    bool statsVisible();

    void displayMessage(sf::String const& message, Color3f const& color = Color3f(0.55f, 1.0f, 1.0f));
}
