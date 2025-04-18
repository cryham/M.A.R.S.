#include "Items/PUShield.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Particles/particles.hpp"


void PUShield::draw() const
{
    if (!collected_)
        PowerUp::draw();
    else
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        for (const auto& it : ships_)
        {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(it->location().x_, it->location().y_, 0.f);

            // shield bubble
            glColor4f(1.0f, 0.5f, 0.8f, 0.9f);
            glBegin(GL_QUADS);
                const int u = 5, v = 0;
                glTexCoord2f(u*0.15625f,     v*0.15625f);     glVertex2f(-35, -35);
                glTexCoord2f(u*0.15625f,     (v+1)*0.15625f); glVertex2f(-35, +35);
                glTexCoord2f((u+1)*0.15625f, (v+1)*0.15625f); glVertex2f(+35, +35);
                glTexCoord2f((u+1)*0.15625f, v*0.15625f);     glVertex2f(+35, -35);
            glEnd();

            glPopMatrix();
        }
    }
}

void PUShield::refreshLifeTime()
{
    lifeTime_ = 0.f;
    totalLifeTime_ = 10.f;
    // direction is abused for texture coords
    particles::spawnMultiple(5, particles::pPowerUpCollect, location_, Vector2f(4,0));
}
