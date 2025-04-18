#include "SpaceObjects/MobileSpaceObject.hpp"
#include "System/settings.hpp"


//  cyclic borders
void MobileSpaceObject::borders()
{
    if (settings::bCyclicBorderX)
    {
        if (location_.x_ < 0.f)
            location_.x_ += settings::iMapXsize;
        
        if (location_.x_ > settings::iMapXsize)
            location_.x_ -= settings::iMapXsize;
    }
    if (settings::bCyclicBorderY)
    {
        if (location_.y_ < 0.f)
            location_.y_ += settings::iMapYsize;
        
        if (location_.y_ > settings::iMapYsize)
            location_.y_ -= settings::iMapYsize;
    }
}
