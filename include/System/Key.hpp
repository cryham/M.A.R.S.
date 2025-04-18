#pragma once

#include <SFML/Window.hpp>

struct Key
{
    Key(sf::Keyboard::Key code);
    Key(unsigned int joyID, sf::Joystick::Axis joyAxis, int strength);
    Key(unsigned int joyID, unsigned int joyButton);

    enum KeyType  {  kKeyBoard, kJoyButton, kJoyAxis  } type_;
    enum NavType  {  nAbort, nConfirm, nDown, nUp, nLeft, nRight, nNone  } navi_;
    enum AxisType {  aLT, aRT, aARup, aARdown, aARleft, aARright, aALup, aALdown,
                     aALleft, aALright, aPOVup, aPOVdown, aPOVleft, aPOVright  };

    union
    {
        sf::Keyboard::Key keyBoard_;
        AxisType          joyAxis_;
        unsigned int      joyButton_;
    }
    code_;

    int strength_;
    unsigned int joyID_;

    static std::pair<AxisType, int> convertFromSFML(sf::Joystick::Axis joyAxis, int strength);
    static sf::Joystick::Axis convertToSFML(AxisType joyAxis);
};

bool operator== (Key const& lhs, Key const& rhs);
std::ostream& operator<< (std::ostream& stream, Key const& input);
std::istream& operator>> (std::istream& stream, Key& output);

