#pragma once

#include "System/Vector2f.hpp"
#include "System/Key.hpp"
#include "Media/music.hpp"

#include <SFML/Graphics.hpp>


/// A namespace handling the main window of the game.

namespace window 
{
    /// Opens the window.
    /// Should be called once at the beginning.
    /// Returns false, if something went wrong.
    bool open();

    /// Recreates the window.
    /// Can be called to apply settings::C_fullScreen.
    void create();

    /// Closes the window.
    /// Should be called once at the end.
    void close();


    /// Starts the main game loop.
    /// Should be called, when the window is opened a game is created.
    void mainLoop();

    /// Starts a draw cycle.
    /// The active OpenGL target is set to the window or the post effect backbuffer, depending
    /// on the use of shaders.
    void startDrawSpace();

    /// Finishs drawing the space and starts drawing the HUD.
    /// Applies post effects and sets the projection matrix to represent the screen in pixels.
    void startDrawHUD();

    /// Draws a SFML drawable in the window.
    void draw(sf::Drawable const& toBeDrawn, sf::RenderStates const& states, sf::Shader* shader = nullptr);


    int isKeyDown(Key const& key);

    Vector2f const getMousePosition();
    Vector2f const getWindowSize();

    void screenShot();

    /// Shows or hides the mouse cursor.
    void showCursor(bool show);

    /// Converts the given location from space coordinates (max (settings::C_MapXsize, C_MapYsize)) to pixel coordinates on the screen.
    Vector2f const coordToPixel(Vector2f const& spaceCoord);

    /// Converts the given location on screen to space coordinates (max (settings::C_MapXsize, C_MapYsize)).
    Vector2f const PixelToCoord(Vector2f const& screenCoord);

    /// Returns a vector representing the size of the visible game area on screen.
    /// In pixels.
    Vector2f const& getViewPort();
}
