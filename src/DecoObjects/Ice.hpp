#pragma once

#include "DecoObjects/DecoObject.hpp"
#include "DecoObjects/decoObjects.hpp"
#include "SpaceObjects/Ball.hpp"
#include "SpaceObjects/Ship.hpp"
#include "Particles/AmmoRocket.hpp"


/// An ice block drawn over frozen SpaceObjects.

template <typename Object>
class Ice : public DecoObject
{
    public:
        Ice(Object* object): object_(object)
        {   }

        //  draw
        void draw() const
        {
            if (object_->visible_ && object_->frozen_ > 0.f)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Ice));
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glPushMatrix();
                glLoadIdentity();
                glTranslatef(object_->location_.x_, object_->location_.y_, 0.f);
                glRotatef(object_->rotation_, 0.f, 0.f, 1.f);
                
                if (object_->frozen_ > 0)
                {
                    int u, v;
                    if (object_->frozen_ >= 30) {  u = 0;  v = 0;  }else
                    if (object_->frozen_ >= 20) {  u = 1;  v = 0;  }else
                    if (object_->frozen_ >= 10) {  u = 0;  v = 1;  }else
                    if (object_->frozen_ > 0)   {  u = 1;  v = 1;  }else
                    {
                        decoObjects::removeIce(this);
                        return;
                    }

                    glColor3f(1.f, 1.f, 1.f);
                    glBegin(GL_QUADS);
                        glTexCoord2f( u*0.5f,    v*0.5f);    glVertex2f(-object_->radius_*1.5f,-object_->radius_*1.5f);
                        glTexCoord2f( u*0.5f,   (v+1)*0.5f); glVertex2f(-object_->radius_*1.5f, object_->radius_*1.5f);
                        glTexCoord2f((u+1)*0.5f,(v+1)*0.5f); glVertex2f( object_->radius_*1.5f, object_->radius_*1.5f);
                        glTexCoord2f((u+1)*0.5f, v*0.5f);    glVertex2f( object_->radius_*1.5f,-object_->radius_*1.5f);
                    glEnd();

                }

                glPopMatrix();

                glDisable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            else
            {
                decoObjects::removeIce(this);
            }
        }

    private:
        Object* object_;
};
