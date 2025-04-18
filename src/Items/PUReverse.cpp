#include "Items/PUReverse.hpp"

#include "SpaceObjects/Ship.hpp"
#include "Players/Player.hpp"
#include "Particles/particles.hpp"


void PUReverse::draw() const
{
    if (!collected_)
    {
        PowerUp::draw();
        return;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (const auto& it : ships_)
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(it->location().x_, it->location().y_ - 40.f, 0.f);
        glScalef(0.7f, 0.7f, 0.f);
        glRotatef(fmod(timer::totalTime()*(-180.f), 360.f), 0.f, 0.f, 1.f);

        // reverse
        glColor3f(1.f, 0.7f, 0.9f);
        glBegin(GL_QUADS);
            const int u = 1, v = 1;
            glTexCoord2f(u*0.15625f,     v*0.15625f);     glVertex2f(-35, -35);
            glTexCoord2f(u*0.15625f,     (v+1)*0.15625f); glVertex2f(-35, +35);
            glTexCoord2f((u+1)*0.15625f, (v+1)*0.15625f); glVertex2f(+35, +35);
            glTexCoord2f((u+1)*0.15625f, v*0.15625f);     glVertex2f(+35, -35);
        glEnd();

        glPopMatrix();
    }
}

void PUReverse::refreshLifeTime()
{
    lifeTime_ = 0.f;
    totalLifeTime_ = 10.f;
    // direction is abused for texture coords
    particles::spawnMultiple(5, particles::pPowerUpCollect, location_, Vector2f(3,0));
}
