#include "DecoObjects/Bolt.hpp"

#include "DecoObjects/decoObjects.hpp"
#include "SpaceObjects/Ball.hpp"
#include "Menu/menus.hpp"
#include "System/randomizer.hpp"


void Bolt::draw() const
{
    if (lifeTime_ <= maxLifeTime_)
    {
        bool ballVisible(false);
        if (to_->type() == spaceObjects::oBall)
        {
            Ball* ball(dynamic_cast<Ball*>(to_));
            ballVisible = ball->isVisible();
        }

        if (to_->type()!=spaceObjects::oBall || ballVisible)
        {
            glPushMatrix();
            glLoadIdentity();

            glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            glEnable(GL_TEXTURE_2D);

            //draw bolts to target

            glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Bolt));

            glColor4f(1.f,1.f,1.f,1.f);

            flickerTimer_ -= timer::frameTime();
            if (flickerTimer_ <= 0.f)
            {   flickerTimer_ = randomizer::random(0.05f, 0.2f);
                boltImage_ = randomizer::random(0,3);
            }

            Vector2f ortho((from_->location()-to_->location()).normalize()*15.f);

            glBegin(GL_QUADS);

            for (int i=0; i < intensity_; ++i)
            {
                int pos = (boltImage_ + i) % 4;
                glTexCoord2f(0.f, 0.f + 0.25f*pos);   glVertex2f(from_->location().x_ - ortho.y_, from_->location().y_ + ortho.x_);
                glTexCoord2f(0.f, 0.25f + 0.25f*pos); glVertex2f(from_->location().x_ + ortho.y_, from_->location().y_ - ortho.x_);
                glTexCoord2f(1.f, 0.25f + 0.25f*pos); glVertex2f(to_->location().x_   + ortho.y_, to_->location().y_   - ortho.x_);
                glTexCoord2f(1.f, 0.f + 0.25f*pos);   glVertex2f(to_->location().x_   - ortho.y_, to_->location().y_   + ortho.x_);
            }
            glEnd();


            // draw cracks on target

            glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Cracks));

            int randomCrack(randomizer::random(0,3));

            Vector2f vec1(Vector2f::randDirLen()*40.f);
            Vector2f vec2(Vector2f::randDirLen()*40.f);
            Vector2f vec3(Vector2f::randDirLen()*40.f);
            Vector2f vec4(Vector2f::randDirLen()*40.f);

            float radius(to_->radius()*2.f);

            glBegin(GL_QUADS);
                glTexCoord2f(0.f, 0.f + 0.25f*randomCrack);   glVertex2f(to_->location().x_-radius+vec1.x_, to_->location().y_-radius+vec1.y_);
                glTexCoord2f(0.f, 0.25f + 0.25f*randomCrack); glVertex2f(to_->location().x_-radius+vec2.x_, to_->location().y_+radius+vec2.y_);
                glTexCoord2f(1.f, 0.25f + 0.25f*randomCrack); glVertex2f(to_->location().x_+radius+vec3.x_, to_->location().y_+radius+vec3.y_);
                glTexCoord2f(1.f, 0.f + 0.25f*randomCrack);   glVertex2f(to_->location().x_+radius+vec4.x_, to_->location().y_-radius+vec4.y_);
            glEnd();

            glDisable(GL_TEXTURE_2D);

            glPopMatrix();
        }
        if (!menus::visible())
            lifeTime_ += timer::frameTime();
    }
    else
        decoObjects::removeBolt(this);
}
