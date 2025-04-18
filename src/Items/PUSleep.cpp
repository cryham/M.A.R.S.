#include "Items/PUSleep.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Particles/particles.hpp"


void PUSleep::draw() const
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
            glTranslatef(it->location().x_, it->location().y_ - 40.f, 0.f);
            glScalef(0.4f, 0.4f, 0.f);

            // sleep zzz
            glColor3f(0.6f, 1.f, 0.4f);
            glBegin(GL_QUADS);
                const int u = 2, v = 0;
                glTexCoord2f(u*0.15625f,     v*0.15625f);     glVertex2f(-35, -35);
                glTexCoord2f(u*0.15625f,     (v+1)*0.15625f); glVertex2f(-35, +35);
                glTexCoord2f((u+1)*0.15625f, (v+1)*0.15625f); glVertex2f(+35, +35);
                glTexCoord2f((u+1)*0.15625f, v*0.15625f);     glVertex2f(+35, -35);
            glEnd();

            glPopMatrix();
        }
    }
}

void PUSleep::refreshLifeTime()
{
    lifeTime_ = 0.f;
    totalLifeTime_ = 5.f;
    // direction is abused for texture coords
    particles::spawnMultiple(5, particles::pPowerUpCollect, location_, Vector2f(2,0));
}
