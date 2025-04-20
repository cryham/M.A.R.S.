#pragma once

#include "System/Vector2f.hpp"
#include "System/Key.hpp"

#include <SFML/Window.hpp>

class UiWindow;
class UiElement;

namespace menus 
{

    void draw();

    // events
    void mouseMoved(Vector2f const& position);
    void mouseWheelMoved(Vector2f const& position, int delta);
    void mouseLeft(bool down);
    void keyEvent(bool down, Key const& key);
    void textEntered(sf::Uint32 keyCode);

    void showMain();
    void showPause();

    void showWindow(UiWindow* toBeShown);
    void hideWindow();
    void hideMenu();

    void clearFocus();
    void fixKeyboardOn(UiElement* target);
    void unFixKeyboard();
    bool keyboardFixed();

    void reload();

    bool visible();
}

