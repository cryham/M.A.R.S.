#pragma once

#include "Interface/UiElement.hpp"
#include "Interface/Label.hpp"

#include <vector>


class Tab: public UiElement
{
    public:
        Tab (const sf::String& text, int width, bool* activated = nullptr);
        ~Tab();

        void mouseMoved(Vector2f const& position);
        void mouseWheelMoved(Vector2f const& position, int delta);
        void mouseLeft(bool down);
        void keyEvent(bool down, Key const& key);
        void textEntered(sf::Uint32 keyCode);

        bool tabNext();
        bool tabPrevious();

        void draw () const;

        void setFocus(UiElement* toBeFocused, bool isPrevious);
        void clearFocus();

        void addWidget (UiElement* toBeAdded);

        /* virtual */
        Vector2f getTopLeft() const;
        bool isActive() const
        {   return active_;  }

        friend class TabList;

    private:
        std::vector<UiElement*> widgets_;
        UiElement* focusedWidget_ = nullptr;
        
        sf::String name_;
        Label* label_ = nullptr;
        bool* activated_ = nullptr;
        bool active_;
};
