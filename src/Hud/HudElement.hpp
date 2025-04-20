#pragma once


class HudElement
{
    public:
        virtual ~HudElement()
        {   }

        virtual void draw() const = 0;
        
        virtual void update()
        {   }
};
