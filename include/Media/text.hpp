#pragma once

#define TEXT_ALIGN_LEFT   0
#define TEXT_ALIGN_CENTER 1
#define TEXT_ALIGN_RIGHT  2

#include "Media/font.hpp"
#include "System/Vector2f.hpp"
#include "System/Color3f.hpp"
#include "System/settings.hpp"

/// A namespace for drawing text on the screen.

namespace text 
{
    /// Draws text to the given space coordinates.
    /// Internally the given space location (from upper left (0, 0) to lower right (settings::C_MapXsize, C_MapYsize))
    /// is transformed to a pixel location on the screen, depending on the current window resolution.
    /// The given location is clamped to the screen resolution, so every text will stay inside the screen.
    /// This function draws the the text exactly on pixels so it won't look blurred due to being drawn
    /// between two pixels. This looks a bit choppy with  moving texts - for those use text::drawMobileSpaceText
    /// instead.
    void drawSpaceText      (sf::String const&, Vector2f const&, float size, int align, Color3f const&, float alpha = 1.f, sf::Font* font = nullptr);

    /// Draws text to the given space coordinates.
    /// Internally the given space location (from upper left (0, 0) to lower right (settings::C_MapXsize, C_MapYsize))
    /// is transformed to a pixel location on the screen, depending on the current window resolution.
    /// The given location is clamped to the screen resolution, so every text will stay inside the screen.
    /// This function won't snap the text to pixels, therefore it can be "in between" two pixels. This will
    /// look blurry, which is fine for moving texts. For static texts use text::drawSpaceText instead.
    void drawMobileSpaceText(sf::String const&, Vector2f const&, float size, int align, Color3f const&, float alpha = 1.f, sf::Font* font = nullptr);

    /// Draws text to the given screen coordinates.
    /// The given location is clamped to the screen resolution, so every text will stay inside the screen.
    void drawScreenText     (sf::String const&, Vector2f const&, float size, int align, Color3f const&, float alpha = 1.f, sf::Font* font = nullptr);

    /// Fixes strange SFML-OpenGL behaviour.
    /// Sometimes, when drawing text on screen, some OpenGL states are messed up, which will lead to non
    /// textured texts which are drawn after. Simply employ this function when drawing text, which causes
    /// such problems. It's kinda hacky and I really don't know what's going on, but, at least, it works.
    /// Any improvement is highly appreciated! This function draws an invisible really small text in the corner
    /// of the screen, which fixes this behaviour.
    void drawFooText();

    /// Returns the position of a character in a string relatively to it's location.
    float getCharacterPos   (sf::String const&, int pos, float size, int align, sf::Font* font = nullptr);
}
