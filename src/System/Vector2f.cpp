#include "System/Vector2f.hpp"

#include "System/randomizer.hpp"

#include <SFML/System.hpp>
#include <cmath>


Vector2f::Vector2f ():
    x_(0.0),
    y_(0.0)
{   }

Vector2f::Vector2f (Vector2f const& point):
    x_(point.x_),
    y_(point.y_)
{   }

Vector2f::Vector2f (float x, float y):
    x_(x),
    y_(y)
{   }

Vector2f Vector2f::normalize() const
{
    float len = length();
    if (len != 0)
        return Vector2f(x_/len, y_/len);
    else
        return Vector2f(0,0);
}

float Vector2f::length() const
{
    return (std::sqrt(x_*x_ + y_*y_));
}

float Vector2f::lengthSquare() const
{
    return x_*x_ + y_*y_;
}

Vector2f const Vector2f::randDir()
{
    float random = randomizer::random(0.0f, 2*M_PI);
    return Vector2f(std::sin(random), std::cos(random));
}

Vector2f const Vector2f::randDirLen()
{
    return randDir() * randomizer::random(0.0f, 1.0f);
}

Vector2f& Vector2f::operator+=(Vector2f const& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

Vector2f& Vector2f::operator-=(Vector2f const& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
}

Vector2f& Vector2f::operator*=(double rhs)
{
    x_ *= rhs;
    y_ *= rhs;
    return *this;
}

Vector2f& Vector2f::operator/=(double rhs)
{
    x_ /= rhs;
    y_ /= rhs;
    return *this;
}

Vector2f operator+ (Vector2f const& lhs, Vector2f const& rhs)
{
    return Vector2f(lhs.x_+rhs.x_, lhs.y_+rhs.y_);
}

Vector2f operator- (Vector2f const& lhs, Vector2f const& rhs)
{
    return Vector2f(lhs.x_-rhs.x_, lhs.y_-rhs.y_);
}

float operator* (Vector2f const& lhs, Vector2f const& rhs)
{
    return (lhs.x_*rhs.x_ + lhs.y_*rhs.y_);
}

Vector2f operator* (Vector2f const& lhs, float rhs)
{
    return Vector2f(lhs.x_*rhs, lhs.y_*rhs);
}

Vector2f operator* (float const& lhs, Vector2f rhs)
{
    return rhs * lhs;
}

Vector2f operator/ (Vector2f const& lhs, float rhs)
{
    return Vector2f(lhs.x_/rhs, lhs.y_/rhs);
}

bool operator== (Vector2f const& lhs, Vector2f const& rhs)
{
    return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_);
}

bool operator!= (Vector2f const& lhs, Vector2f const& rhs)
{
    return (lhs.x_ != rhs.x_ && lhs.y_ != rhs.y_);
}

bool operator< (Vector2f const& lhs, Vector2f const& rhs)
{
    return lhs.lengthSquare() < rhs.lengthSquare();
}

bool operator> (Vector2f const& lhs, Vector2f const& rhs)
{
    return lhs.lengthSquare() > rhs.lengthSquare();
}

bool clockWise(Vector2f const& first, Vector2f const& second)
{
    return (first.x_*second.y_ - first.y_*second.x_) < 0;
}

std::ostream& operator<<(std::ostream& os, Vector2f const& rhs)
{
     return os << "[" << rhs.x_ << ", " << rhs.y_ << "]";
}
