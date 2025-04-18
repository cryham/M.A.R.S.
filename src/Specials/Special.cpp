#include "Specials/Special.hpp"
#include "SpaceObjects/Ship.hpp"


Special::Special(specials::SpecialType type, Ship* parent, sf::String name):
    parent_(parent),
    timer_(0),
    type_(type),
    name_(name)
{   }

void Special::next()
{
    parent_->special_ = specials::createNext(type_, parent_);
    delete this;
}

void Special::previous()
{
    parent_->special_ = specials::createPrev(type_, parent_);
    delete this;
}

void Special::stop()
{
    timer_ = 0.f;
}
