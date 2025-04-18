#include "Specials/NoSpecial.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Games/games.hpp"
#include "Teams/Team.hpp"

#include <SFML/Graphics.hpp>


void NoSpecial::draw(float alpha) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw glow
    parent_->getOwner()->team()->color().brightened().gl4f(0.7f*alpha);

    const float r = parent_->getRadius();
    const int u = 3, v = 3;

    glBegin(GL_QUADS);
        uv4(u, v);     glVertex2f(-r*4,-r*4);
        uv4(u, v+1);   glVertex2f(-r*4, r*4);
        uv4(u+1, v+1); glVertex2f( r*4, r*4);
        uv4(u+1, v);   glVertex2f( r*4,-r*4);
    glEnd();
}
