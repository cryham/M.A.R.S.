#pragma once

#include "System/Vector2f.hpp"
#include "System/Key.hpp"
#include "System/Color3f.hpp"

#include <SFML/Window.hpp>


//  Base for all Gui controls

class UiElement
{
    public:
        UiElement(Vector2f const& topLeft, int width, int height);
        virtual ~UiElement()
        {   }

        virtual void mouseMoved(Vector2f const& position);
        virtual void mouseWheelMoved(Vector2f const& position, int delta) {  }
        virtual void mouseLeft(bool down);
        virtual void keyEvent(bool down, Key const& key) {  }
        virtual void textEntered(sf::Uint32 keyCode) {  }
        virtual bool tabNext()     {  return true;  }
        virtual bool tabPrevious() {  return true;  }

        virtual void draw() const;

        void setParent(UiElement* newParent);
        virtual void setFocus(UiElement* toBeFocused, bool isPrevious);
        virtual void clearFocus();

        bool         isHovered() const {  return hovered_;  }
        bool         isPressed() const {  return pressed_;  }
        bool         isFocused() const {  return focused_;  }
        virtual bool isTopMost() const {  return parent_->isTopMost();  }
        virtual bool isTabable() const {  return true;  }
        virtual Vector2f getTopLeft() const;

        static void setColor4f(float r, float g, float b, float a);
        static void setColor3f(float r, float g, float b);
        static Color3f getColor3f(float r, float g, float b);
    
        static float scale_;

    protected:
        int width() const;

        UiElement* parent_ = nullptr;
        mutable Vector2f topLeft_;
        int width_, height_;

        bool hovered_;
        bool focused_;
        bool pressed_;

        mutable float hoveredFadeTime_;
        mutable float focusedFadeTime_;
};
