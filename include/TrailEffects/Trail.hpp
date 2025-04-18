#pragma once

class SpaceObject;


class Trail
{
    public:
        Trail(SpaceObject* target);
        virtual ~Trail()
        {   }

        virtual void update() = 0;
        virtual void draw() const = 0;
        virtual bool isDead() const = 0;

        void detach();
        SpaceObject* target() const;

    protected:
        SpaceObject* target_ = nullptr;
};
