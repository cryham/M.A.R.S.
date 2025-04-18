#include "Hud/Message.hpp"

#include "Media/text.hpp"
#include "defines.hpp"


Message::Message(sf::String const& message, Color3f const& color):
    text_(message),
    color_(color),
    location_(settings::iMapXsize*0.5f, 200),
    timer_(0.f),
    alpha_(1.f),
    speed_(0.f)
{   }

void Message::draw() const
{
    text::drawMobileSpaceText(text_, location_ + Vector2f(1.f, 1.f),
        20.f, TEXT_ALIGN_CENTER, Color3f(0.f, 0.f, 0.f), alpha_);
    text::drawMobileSpaceText(text_, location_,
        20.f, TEXT_ALIGN_CENTER, color_, alpha_);
}

void Message::update()
{
    timer_ += timer::realFrameTime();
    if (timer_ > 1.f)
    {
        speed_       += timer::realFrameTime();
        location_.y_ += speed_;
        alpha_       -= timer::realFrameTime();
    }
}

bool Message::isDead() const
{
    return timer_ > 2.f;
}
