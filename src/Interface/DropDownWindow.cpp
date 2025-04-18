#include "Interface/DropDownWindow.hpp"

#include "Interface/ComboBox.hpp"
#include "Interface/Button.hpp"
#include "Media/text.hpp"
#include "Media/texture.hpp"
#include "Menu/menus.hpp"

#include <SFML/OpenGL.hpp>


DropDownWindow::DropDownWindow (int width, ComboBox* parent, std::vector<sf::String> elements)
    :UiWindow(200 * scale_, elements.size()*24 + 20),
    parent_(parent),
    elements_(elements.size())
{
    int top(10);
    for (int i=0; i < elements_.size(); ++i)
    {
        elements_[i] = std::make_pair(elements[i], false);
        Button* newOne;
        newOne = new Button(elements_[i].first, "", &(elements_[i].second),
            Vector2f(10, top), width_ / scale_ -20, 20, TEXT_ALIGN_CENTER);
        newOne->setParent(this);
        addWidget(newOne);
        top += 24;
    }
}

void DropDownWindow::checkWidgets()
{
    for (auto& it : elements_)
        if (it.second)
        {   it.second = false;
            *(parent_->currentValue_) = it.first;
            menus::hideWindow();
        }
}

void DropDownWindow::onShow()
{
    for (int i=0; i < elements_.size(); ++i)
        if (elements_[i].first == *parent_->currentValue_)
        {
            if (focusedWidget_)
                focusedWidget_->clearFocus();
            focusedWidget_ = widgets_[i];
            focusedWidget_->setFocus(focusedWidget_, false);
        }
}
