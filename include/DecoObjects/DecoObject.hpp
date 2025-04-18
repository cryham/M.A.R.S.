#pragma once

#include "System/Vector2f.hpp"


/// A simple interface providing just a virtual draw function.

class DecoObject
{
    public:
        virtual ~DecoObject()
        {   }
        virtual void draw() const = 0;
};
